/*
 * colorspace.h
 *
 *  Created on: Aug 11, 2012
 *      Author: bogdan
 */

#ifndef COLORSPACES_H_
#define COLORSPACES_H_

#include<stdbool.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h>

/*The lower limit for R, G, B (real version), S, I*/
#define PER_LOWER_LIMIT (0.0)
/*The upper limit for R, G, B (real version), S, I*/
#define PER_UPPER_LIMIT (1.0)
/*The lower limit for H*/
#define HUE_LOWER_LIMIT (0.0)
/*The upper limit for H*/
#define HUE_UPPER_LIMIT (360.0)
/*The lower limit for R, G, B (integer version)*/
#define RGBI_LOWER_LIMIT (0U)
/*The upper limit for R, G, B (integer version)*/
#define RGBI_UPPER_LIMIT (255U)



/*
=========================================
Validation Functions
=========================================
*/

/*
* Description:
*  Checks if the RGB components are valid
* Parameters:
*  r,g,b - the components of an RGB model expressed
*          as real numbers
* Returns:
*  true if the values are correct
*  false if the values are incorrect
*/bool RgbF_IsValid(double r, double g, double b);

/*
* Description:
*  Checks if the HSL components are valid
* Parameters:
*  h,s,l - the components of an HSL model expressed
*          as real numbers
* Returns:
*  true if the values are correct
*  false if the values are incorrect
*/bool Hsl_IsValid(double h, double s, double l);


/*
* Description:
*  Checks if a value is within a specified interval
* Parameters:
*  value - the value who is checked
*  lowerLimit - the lower limit of the interval
*  upperLimit - the upper limit of the interval
* Returns:
*  true if the value is within the interval
*  false if the value is not within the interval
*/bool RealIsWithinBounds(double value, double lowerLimit, double upperLimit);

/*
======================================== =
Assist Functions
======================================== =
*/
/*
* Description:
*  Returns the largest of the three parameters
* Parameters
*  r,g,b - 3 real numbers
* Returns
*  The largest real number from the set {r,g,b}
*/
double Double_GetMaximum(double r, double g, double b);

/*
* Description:
*  Returns the smallest of the three parameters
* Parameters
*  r,g,b - 3 real numbers
* Returns
*  The smallest real number from the set {r,g,b}
*/
double Double_GetMinimum(double r, double g, double b);

/*
=========================================
Conversion Functions
=========================================
*/

/*
* Description:
*  conver from HSL to RGB.

* Parameters:
*  h,s,l - the components of an HSL model expressed.
*	s,l - 0-100 refer to %.
*          
* Returns:
*  void
*
* Pointer:
*  rr,rg,rb - Int R/G/B value, 0-255
*
*/void ColorSpace_HSL2RGB(double h, double s, double l, uint8_t *rr, uint8_t *rg, uint8_t *rb);

/*
* Description:
*  conver from RGB to HSL.

* Parameters:
*  r,g,b - the components of an RGB model expressed
*          Int 0-255
*
* Returns:
*  void
*
* Pointer:
*  h,s,l - HSL Expressed,
*	s,l - 0-100 refer to %
*
*/void ColorSpace_RGB2HSL(uint8_t r, uint8_t g, uint8_t b, double *h, double *s, double *l);

#endif
