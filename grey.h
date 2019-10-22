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
 * Matrix that can grow dynamically, based on the provided
 * MyVec implementation.
 * 
 */
typedef struct {
    GPx *data;
    int n;
    int x, y;
    int size;
    int max_bright;
} GreyMatrix;


GreyMatrix * CreateGREYMat(int rows, int cols, int max_bright);

GreyMatrix * LoadGREYFromFile(char *);

void SaveGREYOnFile(GreyMatrix *v, char *name);

void PrintGREYMat(GreyMatrix * dm);

void PrintGPx(GPx * px);


#endif //INC_00_GREY_H