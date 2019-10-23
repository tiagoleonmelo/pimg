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




// RGB Functions

DynamicMatrix * CreateMat(int rows, int cols, int max_bright);

DynamicMatrix * LoadFromFile(char *);

void SaveOnFile(DynamicMatrix *v, char *name);

void PrintMat(DynamicMatrix * dm);

void PrintRGBPx(RGBPx * px);

GreyMatrix * ConvertToGreyscale(DynamicMatrix * dm, int channel);

GPx * ConvertPX(RGBPx * px, int channel);


// Greyscale Functions

GreyMatrix * CreateGreyMat(int rows, int cols);

GreyMatrix * LoadGreyFromFile(char *);

void SaveGreyOnFile(GreyMatrix *v, char *name);

void PrintGreyMat(GreyMatrix * dm);

void PrintGPx(GPx * px);


#endif //INC_00_FORMATS_H
