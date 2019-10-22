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
 * Structure that holds the whole image. For each black pixel found,
 * image will store it using masks. The image can later be loading with a
 * XOR operation
 * 
 */
typedef struct{
    unsigned long long image; 
} Bitmap;



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

DynamicMatrix * CreateMat(int rows, int cols, int max_bright);

DynamicMatrix * LoadFromFile(char *);

void SaveOnFile(DynamicMatrix *v, char *name);

void PrintMat(DynamicMatrix * dm);

void PrintRGBPx(RGBPx * px);

DynamicMatrix * ConvertToGreyscale(DynamicMatrix * dm);

RGBPx * MatchRed(RGBPx * pixel);


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

