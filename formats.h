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
    int **a;
    int n;
    int x, y;
    int size;
} DynamicMatrix;

DynamicMatrix * CreateMat(int rows, int cols);

DynamicMatrix * LoadFromFile(char *);

void SaveOnFile(DynamicMatrix *v, char *name);

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
//     RGB matrix[0][0];    // Starting our matrix with dummy values
//                             // memory will be allocated later
// } Imagem;

