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
 * Matrix that can grow dynamically, based on the provided
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



DynamicMatrix * CreateRGBMat(int rows, int cols, int max_bright);

DynamicMatrix * LoadRGBFromFile(char *);

void SaveRGBOnFile(DynamicMatrix *v, char *name);

void PrintRGBMat(DynamicMatrix * dm);

void PrintRGBPx(RGBPx * px);

GreyMatrix * ConvertToGreyscale(DynamicMatrix * dm);

GPx * Greyscale(RGBPx * pixel);


#endif //INC_00_RGB_H