/**
 * 
 * Header that contains DynMat functions and the used structures
 * to store and manipulate images.
 * 
 */

#ifndef INC_00_FORMATS_H
#define INC_00_FORMATS_H

/**
 * 
 * RGB Pixel, used to read an Image in RGB
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
} DynamicMatrix;

DynamicMatrix * CreateMat(int rows, int cols);

DynamicMatrix * LoadFromFile(char *);

void SaveOnFile(DynamicMatrix *v, char *name);

void PrintMat(DynamicMatrix * dm);

void PrintRGBPx(RGBPx * px);

#endif //INC_00_FORMATS_H

// Move these to a different module
// typedef struct{
//     int y;
// } Greyscale;

// typedef struct{
//     int byte[8]; 
// } Byte;

// typedef struct{
//     int height;
//     int length;
//     RGB matrix[0][0]; 
// } Imagem;

