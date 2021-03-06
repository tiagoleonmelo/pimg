/**
 * 
 * \file rgb.c
 * <h2>RBG Image Manipulation</h2>
 * 
 * The RBG module contains methods for<ul>
 * <li>reading</li>
 * <li>writing</li>
 * <li>converting RGB images to Greyscale</li>
 * </ul>
 * 
 * @param Authors João Nogueira, Tiago Melo
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "../lib/rgb.h"
#include "../lib/grey.h"
#include "../lib/filters.h"

#define NONE 0
#define RED 1
#define GREEN 2
#define BLUE 3


/**
 * 
 * Create a RGB Matrix, composed of RGBPixels
 * 
 * The matrix to return has rows and cols columns.
 * 
 * Its maximum RGB value is given by   max_bright
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
    fscanf(fp, "%d\n", &max_bright);


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
    fprintf(fp, "%d\n", dm->max_bright);

    // Writing data
    fwrite(dm->data, 3 * dm->x, dm->y, fp);

    fclose(fp);
}


/**
 * 
 * Print a RGB Matrix   dm on the console
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
 * Access the position at [row][col] in the matrix   dm
 * 
 */
RGBPx * AccessRGBPx(DynamicMatrix * dm, int row, int col){
    int index = (row * dm->x) + col;
    return &(dm->data[index]);
}


/**
 * 
 * Access a given ROI. Top left pixel is at ( x1, y1) and bottom right pixel is
 * at (x2, y2). Returns the sub-matrix from   dm that follows these conditions.
 *  * 
 */
DynamicMatrix * AccessRegion(DynamicMatrix * gm, int x1, int y1, int x2, int y2)
{

    DynamicMatrix * sub = CreateMat(x2 - x1, y2 - y1, gm->max_bright);

    RGBPx * img_source = gm->data;
    RGBPx * buffer = malloc(sub->size * sizeof(RGBPx));

    int counter = 0;


    for(int i = 0; i < gm->size; i++)
    {

        // Checking if i is within the bounds of the ROI
        if(RGBChecker(gm, y1, x1, y2 + 1, x2 + 1, i))
        {

            buffer[counter] = img_source[i];

            counter++;

        }


    }


    sub->data = buffer;

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



// Convertion Methods

/**
 * 
 * Function that converts an RGB Matrix dm to a Greyscale matrix
 * and returns it.
 * 
 * Essentially, it iterates through the RGB data, converts it and stores it in
 * a buffer. This buffer is then used as the new Greyscale Matrix's data.
 * 
 * channel is an argument that allows the user to select a channel of color into which
 * the RGB Matrix will be split. If NONE is specified, the Greyscale image generated will be
 * an overlap of the Red, Green and Blue Greyscale images.
 * 
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
 *   channel follows the same logic as above, i. e., when NONE is specified,   px will be
 * converted using a formula that takes into consideration every color component. Otherwise, it
 * considers only the color component given.
 * 
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
        tmp->grey = (30 * px->r + 59 * px->g + 11 * px->b) / 100;
        break;
    
    }


    return tmp;
}