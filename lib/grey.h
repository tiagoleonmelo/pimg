/**
 * 
 * Header that contains DynMat functions for the Greyscale Module
 * 
 */

#ifndef INC_00_GREY_H
#define INC_00_GREY_H
#include "rgb.h"

/**
 * 
 * Greyscale Pixel, used to read an Image into Greyscale format
 * Contains a single value, holding the "amount of grey" in that pixel
 * 
 */
typedef struct{
    unsigned char grey;
} GPx;



/**
 * 
 * GREY Matrix that can grow dynamically, based on the provided
 * MyVec implementation.
 * 
 */
typedef struct {
    GPx *data;
    int n;
    int x, y;
    int size;
} GreyMatrix;


// Greyscale Functions

GreyMatrix * CreateGreyMat(int rows, int cols);

GreyMatrix * LoadGreyFromFile(char *);

void SaveGreyOnFile(GreyMatrix *v, char *name);

void PrintGreyMat(GreyMatrix * dm);

GPx * AccessGPx(GreyMatrix * dm, int row, int col);

void PrintGPx(GPx * px);

unsigned int * ConvertToBitMat(GreyMatrix * gm);

GreyMatrix * ConvertToBitGreyMat(GreyMatrix * gm, int threshold);

unsigned int ConvertToBit(int pixels[]);


#endif //INC_00_GREY_H