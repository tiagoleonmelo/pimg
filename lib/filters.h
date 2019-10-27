/**
 * 
 * Header that contains the appliable filters to an image
 * 
 * 
 */

#ifndef INC_00_FILTERS_H
#define INC_00_FILTERS_H

#include "../lib/rgb.h"
#include "../lib/grey.h"
#include "../lib/bit.h"

DynamicMatrix * Saturate(DynamicMatrix * dm, int value);

GreyMatrix * SaturateGrey(GreyMatrix * dm, int value);


DynamicMatrix * FilterRGB(DynamicMatrix * gm, int kernel[], int size);

GreyMatrix * FilterGrey(GreyMatrix * gm, int kernel[], int size);


DynamicMatrix * WatermarkRGB(DynamicMatrix * gm, DynamicMatrix * watermark, int x_start, int y_start);

GreyMatrix * WatermarkGrey(GreyMatrix * gm, GreyMatrix * watermark, int x_start, int y_start);


int RGBChecker(DynamicMatrix * gm, int x0, int y0, int x1, int y1, int i);

int GreyChecker(GreyMatrix * gm, int x0, int y0, int x1, int y1, int i);








#endif //INC_00_FILTERS_H
