/*
 * colorspacebody.c
 *
 *  Created on: Aug 11, 2012
 *      Author: bogdan
 */
#include "colorspace.h"


bool Hsl_IsValid(double h, double s, double l)
{
	bool isValid = true;
	if ((RealIsWithinBounds(h, HUE_LOWER_LIMIT, HUE_UPPER_LIMIT) == false)
		|| (RealIsWithinBounds(s, PER_LOWER_LIMIT, PER_UPPER_LIMIT) == false)
		|| (RealIsWithinBounds(l, PER_LOWER_LIMIT, PER_UPPER_LIMIT) == false))
	{
		isValid = false;
	}
	return isValid;
}

bool RgbF_IsValid(double r, double g, double b)
{
	bool isValid = true;
	if ((RealIsWithinBounds(r, PER_LOWER_LIMIT, PER_UPPER_LIMIT) == false)
		|| (RealIsWithinBounds(g, PER_LOWER_LIMIT, PER_UPPER_LIMIT) == false)
		|| (RealIsWithinBounds(b, PER_LOWER_LIMIT, PER_UPPER_LIMIT) == false))
	{
		isValid = false;
	}
	return isValid;
}

bool RealIsWithinBounds(double value, double lowerLimit, double upperLimit)
{
	if (value >= lowerLimit && value <= upperLimit)
	{
		return true;
	}
	else
	{
		return false;
	}
}

double Double_GetMinimum(double r, double g, double b)
{
	if (r < g)
	{
		if (r < b)
		{
			return r;
		}
		else
		{
			return b;
		}
	}
	else
	{
		if (g < b)
		{
			return g;
		}
		else
		{
			return b;
		}
	}
	return 0;
}

double Double_GetMaximum(double r, double g, double b)
{
	if (r > g)
	{
		if (r > b)
		{
			return r;
		}
		else
		{
			return b;
		}
	}
	else
	{
		if (g > b)
		{
			return g;
		}
		else
		{
			return b;
		}
	}
	return 0;
}

void ColorSpace_HSL2RGB(double h, double s, double l, uint8_t *rr, uint8_t *rg, uint8_t *rb)
{
	//RgbFColor* color = NULL;
	s = s / 100;
	l = l / 100;

	double c = 0.0, m = 0.0, x = 0.0;
	double R, G, B;
	double MC, MX, M;
	if (Hsl_IsValid(h, s, l) == true)
	{
		c = (1.0 - fabs(2 * l - 1.0)) * s;
		m = 1.0 * (l - 0.5 * c);
		x = c * (1.0 - fabs(fmod(h / 60.0, 2) - 1.0));

		MC = c + m;
		MX = x + m;
		M = m;

		if (h >= 0.0 && h < (HUE_UPPER_LIMIT / 6.0))
		{
			//color = RgbF_Create(c + m, x + m, m);
			R = MC;
			G = MX;
			B = M;
		}
		else if (h >= (HUE_UPPER_LIMIT / 6.0) && h < (HUE_UPPER_LIMIT / 3.0))
		{
			//color = RgbF_Create(x + m, c + m, m);
			R = MX;
			G = MC;
			B = M;
		}
		else if (h >= (HUE_UPPER_LIMIT / 3.0) && h < (HUE_UPPER_LIMIT / 2.0))
		{
			//color = RgbF_Create(m, c + m, x + m);
			R = M;
			G = MC;
			B = MX;
		}
		else if (h >= (HUE_UPPER_LIMIT / 2.0)
			&& h < (2.0f * HUE_UPPER_LIMIT / 3.0))
		{
			//color = RgbF_Create(m, x + m, c + m);
			R = M;
			G = MX;
			B = MC;
		}
		else if (h >= (2.0 * HUE_UPPER_LIMIT / 3.0)
			&& h < (5.0 * HUE_UPPER_LIMIT / 6.0))
		{
			//color = RgbF_Create(x + m, m, c + m);
			R = MX;
			G = M;
			B = MC;
		}
		else if (h >= (5.0 * HUE_UPPER_LIMIT / 6.0) && h < HUE_UPPER_LIMIT)
		{
			//color = RgbF_Create(c + m, m, x + m);
			R = MC;
			G = MX;
			B = M;
		}
		else
		{
			//color = RgbF_Create(m, m, m);
			R = M;
			G = M;
			B = M;
		}
	}
	*rr = (uint8_t)(R * 255);
	*rg = (uint8_t)(G * 255);
	*rb = (uint8_t)(B * 255);

}

void ColorSpace_RGB2HSL(uint8_t r, uint8_t g, uint8_t b, double *h, double *s, double *l)
{
	double rR = (double)r / 255, rG = (double)g / 255, rB = (double)b / 255;

	double M = 0.0, m = 0.0, c = 0.0;
	//HslColor* color = NULL;
	double H, S, L;


	if (RgbF_IsValid(rR, rG, rB) == true)
	{
		double H, S, L;

		M = Double_GetMaximum(rR, rG, rB);
		m = Double_GetMinimum(rR, rG, rB);
		c = M - m;
		//color = Hsl_Create(0.0, 0.0, 0.0);
		L = 0.5 * (M + m);
		if (c != 0.0)
		{
			if (M == rR)
			{
				H = fmod(((rG - rB) / c), 6.0);
			}
			else if (M == rG)
			{
				H = ((rB - rR) / c) + 2.0;
			}
			else/*if(M==b)*/
			{
				H = ((rR - rG) / c) + 4.0;
			}
			H *= 60.0;
			S = c / (1.0 - fabs(2.0 * L - 1.0));
		}
		*h = round(H);
		*s = round(S * 100);
		*l = round(L * 100);
		
	}
	//return color;
}