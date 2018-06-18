#include "NeoPixel_WS2812B.h"
//#include "stm32f1xx_hal.h"
#include "string.h"




void WS28_init(WS28_HandleTypeDef *hws28)
{
	hws28->BuffLen = hws28->PixelLen * 24;
	hws28->pPixelBuffer = (uint32_t*)calloc(hws28->PixelLen, sizeof(uint32_t));
	hws28->pSendBuffer = (uint8_t*)calloc(hws28->BuffLen, sizeof(uint8_t));
	WS28_SET_COLOR_ALL(hws28, WS28_RGB2COLOR(0, 0, 0));
}

void WS28_REFRESH(WS28_HandleTypeDef *hws28)
{
	if (hws28->state == READY)
	{
		while (HAL_SPI_GetState(hws28->hspi) != HAL_SPI_STATE_READY) {};
		hws28->state = BUSY;
		HAL_SPI_Transmit_DMA(hws28->hspi, hws28->pSendBuffer, hws28->BuffLen);
	}
}

// Color Conversion

uint32_t WS28_RGB2COLOR(uint8_t r, uint8_t g, uint8_t b)
{
	return (((uint32_t)g << 16) | ((uint32_t)r << 8) | b);

}

uint32_t WS28_HSL2COLOR(double H, double S, double L)
{
	uint8_t r, g, b;
	ColorSpace_HSL2RGB(H, S, L, &r, &g, &b);
	return WS28_RGB2COLOR(r, g, b);
}

void WS28_COLOR2BIT(uint32_t color, uint8_t *colorbit)
{
	//printf("COLORBIT: In COLOR:%6X\n", color);
	for (int i = 24;i > 0;i--)
	{

		switch (color & 0x1)
		{
		case 0:
			colorbit[i - 1] = BIT0;
			//printf("0");
			break;

		case 1:
			colorbit[i - 1] = BIT1;
			//printf("1");
			break;

		default:
			break;
		}
		/*
		switch (i)
		{
		case 7:
			printf(" ");
			break;
		case 15:
			printf(" ");
			break;
		case 23:
			printf(" \n");
			break;
		default:
			break;
		}
		*/
		color = color >> 1;
	}

}

void WS28_GET_PIXEL_RGB(uint32_t color, uint8_t *r, uint8_t *g, uint8_t *b)
{

	*b = (uint8_t)color;
	*r = (uint8_t)(color >> 8);
	*g = (uint8_t)(color >> 16);
}

// Set Color Section

void WS28_SET_COLOR_ALL(WS28_HandleTypeDef *hws28, uint32_t color)
{
	uint8_t colorbit[24];

	WS28_COLOR2BIT(color, colorbit);

	for (int i = 0;i < hws28->PixelLen;i++)
	{
		memcpy(hws28->pSendBuffer + (24 * i), &colorbit, 24);
		hws28->pPixelBuffer[i] = color;
	}

	hws28->state = READY;
	WS28_REFRESH(hws28);
}

void WS28_SET_COLOR_PIXEL(WS28_HandleTypeDef *hws28, uint8_t pos, uint32_t color)
{
	uint8_t colorbit[24];

	WS28_COLOR2BIT(color, colorbit);

	memcpy(hws28->pSendBuffer + (24 * pos), &colorbit, 24);
	hws28->pPixelBuffer[pos] = color;

	hws28->state = READY;
	WS28_REFRESH(hws28);
}

void WS28_SET_BRIGHTNESS(WS28_HandleTypeDef *hws28, uint8_t scale)
{
	if (scale >= 0 && scale <= 100) hws28->Brightness = scale;

	uint8_t colorbit[24];
	uint32_t pixelcolor;
	uint8_t r, g, b;
	double h, s, l;


	for (uint8_t i = 0; i < hws28->PixelLen;i++)
	{
		pixelcolor = hws28->pPixelBuffer[i];

		// Extract RGB from PIXEL
		WS28_GET_PIXEL_RGB(hws28->pPixelBuffer[i], &r, &g, &b);

		// Convert RGB to HSL
		ColorSpace_RGB2HSL(r, g, b, &h, &s, &l);

		// Update Pixel with new RGB.
		hws28->pPixelBuffer[i] = WS28_HSL2COLOR(h, s, hws28->Brightness);
		
		WS28_COLOR2BIT(hws28->pPixelBuffer[i], colorbit);

		memcpy(hws28->pSendBuffer + (24 * i), &colorbit, 24);

		hws28->pPixelBuffer[i] = WS28_RGB2COLOR(r, g, b);
	}

	hws28->state = READY;
	WS28_REFRESH(hws28);
}
