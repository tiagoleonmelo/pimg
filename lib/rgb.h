/**
 * 
 * Header that contains DynMat functions for the RGB Module

 * 
 */

#ifndef INC_00_RGB_H
#define INC_00_RGB_H
#include "grey.h"



/**
 * 
 * RGB Pixel, used to read an Image in RGB
 * Contains 3 distinct values, one for each color
 * 
 */
typedef struct{
    unsigned char r,g,b;
} RGBPx;




/**
 * 
 * RGB Matrix that can grow dynamically, based on the provided
 * MyVec implementation.
 * 
 */
typedef struct {
    RGBPx *data;
    int n;
    int x, y;
    int size;
    int max_bright;
} DynamicMatrix;

// RGB Functions

DynamicMatrix * CreateMat(int rows, int cols, int max_bright);

DynamicMatrix * LoadFromFile(char *);

void SaveOnFile(DynamicMatrix *v, char *name);

void PrintMat(DynamicMatrix * dm);

RGBPx * AccessRGBPx(DynamicMatrix * dm, int row, int col);

DynamicMatrix * AccessRegion(DynamicMatrix *dm, int x1, int y1, int x2, int y2);

void PrintRGBPx(RGBPx * px);

GreyMatrix * ConvertToGreyscale(DynamicMatrix * dm, int channel);

GPx * ConvertPX(RGBPx * px, int channel);


#endif //INC_00_RGB_H