/**
 * 
 * Header that contains the appliable filters to an image
 * 
 * 
 * SUPPORTED OPERATIONS
 *  >Increase Saturation/Vibrance
 *  >
 * 
 */

#ifndef INC_00_FILTERS_H
#define INC_00_FILTERS_H

#include "../lib/rgb.h"
#include "../lib/grey.h"
#include "../lib/bit.h"

DynamicMatrix * Saturate(DynamicMatrix * dm, int value);

GreyMatrix * SaturateGrey(GreyMatrix * dm, int value);



GreyMatrix * Filter(GreyMatrix * gm, int size);












#endif //INC_00_FILTERS_H
