/**
 * 
 * Header that contains DynMat functions and the pixel formats used
 * to store and manipulate images.
 * 
 */

#ifndef INC_00_FORMATS_H
#define INC_00_FORMATS_H

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
 * Greyscale Pixel, used to read an Image into Greyscale format
 * Contains a single value, holding the "amount of grey" in that pixel
 * 
 */
typedef struct{
    unsigned char grey;
} GPx;


/**
 * 
 * Data structure
 * 
 */
typedef struct{
    unsigned int bit : 1; 
} Bit;



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


/**
 * 
 * BIT Matrix that can grow dynamically, based on the provided
 * MyVec implementation.
 * 
 */
typedef struct {
    Bit *data;
    int x, y;
    int size;
} BitMatrix;


/**
 * 
 * BitMap Image processing is done via integer array, where each position of the array
 * holds 32 values (4 bytes * 8 bits)
 * 
 * Hope it works lmao
 * 
 */




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


// Greyscale Functions

GreyMatrix * CreateGreyMat(int rows, int cols);

GreyMatrix * LoadGreyFromFile(char *);

void SaveGreyOnFile(GreyMatrix *v, char *name);

void PrintGreyMat(GreyMatrix * dm);

GPx * AccessGPx(GreyMatrix * dm, int row, int col);

void PrintGPx(GPx * px);


// Bit Functions

int *  CreateBitMat(int rows, int cols);

int * LoadBitMatFromFile(char *);

void SaveBitMatOnFile(int *mat, char *name);

void PrintBitMat(int *mat);

void PrintBit(int index);

#endif //INC_00_FORMATS_H
