/**
 * 
 * Dynamic Matrix
 * 
 * The DynMat module will read from a ppm file and internally create a matrix
 * as it reads. This representation of an image can and will then be written
 * to a file.
 * 
 * There will also be the options of manipulating an image, but at the time of writing
 * that is just TODO
 * 
 * Also TODO: Split the contents of this file into different headers
 * 
 * @param Authors João Nogueira, Tiago Melo
 * 
 */
#include "../lib/formats.h"
#include <stdlib.h>
#include <stdio.h>

#define NONE 0
#define RED 1
#define GREEN 2
#define BLUE 3

/**
 * 
 * Create a RGB Matrix
 * 
 */
DynamicMatrix * CreateMat(int rows, int cols, int max_bright)
{
    DynamicMatrix *tmp;

    tmp = (DynamicMatrix*)malloc(sizeof(DynamicMatrix));
    tmp->n = 0;

    tmp->x = rows;
    tmp->y = cols;
    
    tmp->size = rows*cols;

    tmp->max_bright = max_bright;

    tmp->data = (RGBPx *)calloc(tmp->size, sizeof(int));

    return tmp;
}


/**
 * 
 * Load a RGB Matrix from file called name
 * 
 */
DynamicMatrix * LoadFromFile(char *name)
{
    FILE *fp = fopen(name, "rb");
    char buff[16];
    
    // Reading the image format
    if (!fgets(buff, sizeof(buff), fp)) {
        exit(1);
    }

    // Checking the image format
    if (buff[0] != 'P' || buff[1] != '6') {
         fprintf(stderr, "Invalid image format (must be 'P6')\n");
         exit(1);
    }

    int x, y, max_bright;
    
    fscanf(fp, "%d", &x);
    fscanf(fp, "%d", &y);
    fscanf(fp, "%d", &max_bright);


    DynamicMatrix *tmp = CreateMat(x, y, max_bright);
    fread(tmp->data, 3 * tmp->x, tmp->y, fp);

    return tmp;
}


/**
 * 
 * Save a RGB Matrix dm to file called name
 * 
 */
void SaveOnFile(DynamicMatrix *dm, char *name)
{
    FILE *fp = fopen(name, "wb");

    // Writing the image format
    fprintf(fp, "P6\n");

    // Writing rows, columns and maximum brightness
    fprintf(fp, "%d %d\n", dm->x, dm->y);
    fprintf(fp, "%d", dm->max_bright);

    // Writing data
    fwrite(dm->data, 3 * dm->x, dm->y, fp);

    fclose(fp);
}


/**
 * 
 * Print a RGB Matrix dm on the console
 * 
 */
void PrintMat(DynamicMatrix *dm)
{

    RGBPx * array_ptr = dm->data;

    for(int i = 0; i <= dm->size; i++){
        PrintRGBPx(array_ptr);
        array_ptr++;
    }

    printf("\n");
}


/**
 * 
 * Access the position at [row][col] in the matrix dm
 * 
 */
RGBPx * AccessRGBPx(DynamicMatrix * dm, int row, int col){
    int index = (row * dm->x) + col;
    return &(dm->data[index]);
}


/**
 * 
 * DOESN'T WORK
 * 
 */
DynamicMatrix * AccessRegion(DynamicMatrix *dm, int x1, int y1, int x2, int y2)
{

    int cols = x2 - x1;
    int rows = y2 - y1;
    int index1 = (x1-1) * dm->x + (y1-1);
    int index2 = (x2-1) * dm->x + (y2-1);
    RGBPx * ptr;

    // Lazy implementation of the abs() function

    if (rows < 0)
    {
        rows *= -1;
    }
    
    if (cols < 0)
    {
        cols *= -1;
    }

    DynamicMatrix * sub = CreateMat(rows, cols, dm->max_bright);
    int counter = 0;

    if (index1 < index2)
    {
        ptr = dm->data + index1;
        RGBPx buffer[index2 - index1];
        printf("DM %d\n", dm->size);
        printf("SUB %d\n", sub->size);
        printf("IDXDIFF %d\n", index2 - index1);

        for (int i = index1; i < index2; i++)
            {
                // Update buffer data
                buffer[counter] = *ptr;
                counter++;
                ptr++;
            }

        sub->data = buffer;

    }
    else
    {
        ptr = dm->data + index2;
        RGBPx buffer[index1 - index2];

        for (int i = index2; i < index1; i++)
            {
                // Update sub data
                buffer[counter] = *ptr;
                counter++;
                ptr++;
            }

        sub->data = buffer;

    }
    

    return sub;
    
}


/**
 * 
 * Print a RGB Pixel in the form [R, G, B]
 * 
 */
void PrintRGBPx(RGBPx *px)
{
    printf("[ %d, %d, %d ]", px->r, px->g, px->b);
}


/**
 * 
 * Function that converts an RGB Matrix dm to a Greyscale matrix
 * and returns it.
 * 
 * Essentially, it iterates through the RGB data, converts it and stores it in
 * a buffer. This buffer is then used as the new Greyscale Matrix's data.
 * 
 */
GreyMatrix * ConvertToGreyscale(DynamicMatrix *dm, int channel)
{

    GreyMatrix * ret = CreateGreyMat(dm->x, dm->y);
    RGBPx *source = dm->data;

    GPx buffer[dm->size];

    GPx *new_px;

    for (int i = 0; i < dm->size; i++)
    {
        new_px = ConvertPX(source, channel); 

        buffer[i] = *new_px;

        source++;
    }

    ret->data = buffer;


    return ret;
    
}


/**
 * 
 * Convert an RGB pixel into a Greyscale pixel, by means of color component averaging
 * 
 */
GPx * ConvertPX(RGBPx * px, int channel)
{
    GPx * tmp = (GPx *)malloc(sizeof(GPx));

    switch (channel)
    {
    case RED:
        tmp->grey = px->r;
        break;
    
    case GREEN:
        tmp->grey = px->g;
        break;

    case BLUE:
        tmp->grey = px->b;
        break;


    default:
        tmp->grey = (px->r + px->g + px->b) / 3;
        break;
    }


    return tmp;
}


/**
 * 
 * Create a Greyscale Matrix
 * 
 */
GreyMatrix * CreateGreyMat(int rows, int cols)
{
    GreyMatrix *tmp;

    tmp = (GreyMatrix*)malloc(sizeof(GreyMatrix));
    tmp->n = 0;

    tmp->x = rows;
    tmp->y = cols;
    
    tmp->size = rows*cols;


    tmp->data = (GPx *)calloc(tmp->size, sizeof(int));

    return tmp;
}


/**
 * 
 * Load a Greyscale Matrix from a file called name TODO: FIX THIS
 * 
 */
GreyMatrix * LoadGreyFromFile(char * name)
{
    FILE *fp = fopen(name, "rb");
    char buff[16];
    
    // Reading the image format
    if (!fgets(buff, sizeof(buff), fp)) {
        exit(1);
    }

    // Checking the image format
    if (buff[0] != 'P' || buff[1] != '5') {
         fprintf(stderr, "Invalid image format (must be 'P6')\n");
         exit(1);
    }

    int x, y, max_bright;
    
    fscanf(fp, "%d", &x);
    fscanf(fp, "%d", &y);
    fscanf(fp, "%d", &max_bright);


    GreyMatrix *tmp = CreateGreyMat(x, y);
    fread(tmp->data, tmp->x, tmp->y, fp);

    return tmp;
}


/**
 * 
 * Save a Greyscale Matrix gm to a file called name TODO: FIX THIS
 * Right now this is saving three images for some reason? IDK Error might be in
 * conversion
 * 
 */
void SaveGreyOnFile(GreyMatrix *gm, char *name)
{
    FILE *fp = fopen(name, "wb");

    // Writing the image format
    fprintf(fp, "P5\n");

    // Writing rows, columns and maximum brightness
    fprintf(fp, "%d %d\n", gm->x, gm->y);
    fprintf(fp, "%d\n", 255);

    // Writing data
    fwrite(gm->data, gm->x, gm->y, fp);
}


/**
 * 
 * Print a Greyscale Matrix gm on the console
 * 
 */
void PrintGreyMat(GreyMatrix * dm){
    GPx * array_ptr = dm->data;

    for(int i = 0; i <= dm->size; i++){
        PrintGPx(array_ptr);
        array_ptr++;
    }

    printf("\n");
}


/**
 * 
 * Access the position at [row][col] in the matrix dm
 * 
 */
GPx * AccessGPx(GreyMatrix * dm, int row, int col){
    int index = row * dm->x + col;
    return &(dm->data[index]);
}


/**
 * 
 * Print a Greyscale Pixel
 * 
 */
void PrintGPx(GPx * px){
    printf("%d ", px->grey);
}


/**
 * 
 * TODO:
 * 
 * Function that converts a Greyscale Matrix gm to a BitMap matrix
 * and returns it.
 * 
 * It iterates through Greyscale data, matches it with a user given threshold and
 * creates a Bit based on that operation.
 * 
 */
int *  CreateBitMat(int rows, int cols){

    // Allocate enough memory for rows * cols pixels
    int * tmp = (int *)malloc((rows * cols) / 32);

    return tmp;
}

// int * LoadBitMatFromFile(char * name){

//     FILE *fp = fopen(name, "rb");
//     char buff[16];
    
//     // Reading the image format
//     if (!fgets(buff, sizeof(buff), fp)) {
//         exit(1);
//     }

//     // Checking the image format
//     if (buff[0] != 'P' || buff[1] != '4') {
//          fprintf(stderr, "Invalid image format (must be 'P4')\n");
//          exit(1);
//     }

//     int x, y, max_bright;
    
//     fscanf(fp, "%d", &x);
//     fscanf(fp, "%d", &y);
//     fscanf(fp, "%d", &max_bright);


//     int *tmp = CreateBitMat(x, y);
//     fread(tmp, , tmp->y, fp);

//     return tmp;
// }

