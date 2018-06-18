
#ifndef NEOPIXEL_WS2812B_H
#define NEOPIXEL_WS2812B_H

#include "stm32f1xx_hal.h"
#include "spi.h"

#define BIT1		0x78  // b 0111 1110
#define BIT0		0x60	// b 0110 0000


/*The lower limit for H*/
#define HUE_LOWER_LIMIT (0.0)
/*The upper limit for H*/
#define HUE_UPPER_LIMIT (360.0)


typedef enum
{
	BUSY = 0x00U,
	READY = 0x01U,
	UPDATE = 0x02U
} BSP_UpdateEnumDef;

typedef struct
{
	SPI_HandleTypeDef*	hspi;
	uint32_t*			pPixelBuffer;			/*!< 缓存指针        */
	uint8_t*			pSendBuffer;			/*!< 发送指针        */
	uint8_t 			Brightness;			/*!< 亮度参数        */
	uint16_t           	PixelLen;			/*!< 像素数量        */
	uint16_t           	BuffLen;			/*!< 缓存长度        */
	__IO BSP_UpdateEnumDef    state;		/*!< 状态            */
} WS28_HandleTypeDef;


void WS28_init(WS28_HandleTypeDef *hws28);

//void WS28_REFRESH(WS28_HandleTypeDef *hws28);

uint32_t WS28_RGB2COLOR(uint8_t r, uint8_t g, uint8_t b);

uint32_t WS28_HSL2COLOR(double H, double S, double L);


//void WS28_COLOR2BIT(uint32_t color, uint8_t *colorbit);


void WS28_SET_BRIGHTNESS(WS28_HandleTypeDef *hws28, uint8_t scale);

void WS28_SET_COLOR_ALL(WS28_HandleTypeDef *hws28, uint32_t color);

void WS28_SET_COLOR_PIXEL(WS28_HandleTypeDef *hws28, uint8_t pos, uint32_t color);

//void WS28_GET_PIXEL_RGB(uint16_t color, uint8_t *r, uint8_t *g, uint8_t *b);


#endif // ADAFRUIT_NEOPIXEL_H
