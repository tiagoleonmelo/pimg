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
    fprintf(fp, "%d\n", dm->max_bright);

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

    int rows = x2 - x1 + 1;
    int cols = y2 - y1 + 1;
    int index1 = (x1 * dm->x) + y1;
    int index2 = (x2 * dm->x) + y2;


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
    RGBPx buffer[sub->size]; //

    int counter = 0;
    int jump;
    int help = 0;

    if (index1 < index2)
    {
        jump = x1 + (dm->y - x2);

        for (int i = index1; i < index2; i++)
            {
                // Update buffer data
                buffer[counter] = dm->data[i];
                counter++;
                help++;

                if(help == sub->y)
                {
                    i+=jump;
                    help = 0;
                }

            }

        sub->data = buffer;

    }
    else
    {
        jump = x2 + (dm->y - x1);

        for (int i = index2; i < index1; i++)
            {
                // Update buffer data
                buffer[counter] = dm->data[i];
                counter++;
                help++;

                if(help == sub->y)
                {
                    i+=jump;
                    help = 0;
                }
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

    GPx *buffer = malloc(dm->size * sizeof(GPx));

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
        tmp->grey = (30 * px->r + 59 * px->g + 11 * px->b) / 100;
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
 * Save a Greyscale Matrix gm to a file called name
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
 * 
 * Function that converts a Greyscale Matrix gm to a BitMap matrix
 * and returns it.
 * 
 * It iterates through Greyscale data, matches it with a user given threshold and
 * creates a Bit based on that operation.
 * 
 * An array of masks is then returned
 * 
 */
unsigned int * ConvertToBitMat(GreyMatrix * gm)
{

    GPx *source = gm->data;

    // We have an int array. Each slot has 32 bits. If we want to store 32 pixels we only
    // need 1 slot. Math explained.
    unsigned int * buffer = malloc(sizeof(unsigned int) * gm->size/32);
    int short_buffer[32];
    unsigned int new_px;

    for(int i = 0; i < gm->size/32; i++){
        buffer[i] = 0;
    }



    for (int i = 0; i < gm->size /32; i++)
    {

        for (int j = 0; j < 32; j++)
        {
            short_buffer[j] = source->grey;
            source++;
        }
        
        new_px = ConvertToBit(short_buffer); 

        buffer[i] = new_px;

    }


    // for(int i = 0; i < gm->size/32; i++){
    //     printf("%u; ", buffer[i]);
    // }


    
    return buffer;
    
}

/**
 * 
 * Big hack: instead of saving the image using bits, save it in greymap, where a 1 is replaced with
 * 255 and a 0 replaced with 0.
 * 
 * The bit array implementation explained above didnt quite work, 
 * so we went for this one instead.
 * 
 */
GreyMatrix * ConvertToBitGreyMat(GreyMatrix * gm, int threshold)
{

    GPx *source = gm->data;
    GreyMatrix * ret = CreateGreyMat(gm->x, gm->y);
    GPx new_px;
    GPx buffer[gm->size];

    for (int i = 0; i < gm->size; i++)
    {

        new_px = *source;

        if (source->grey >= threshold)
        {
            new_px.grey = 255;
        }
        else
        {
            new_px.grey = 0;
        }
        
        
        buffer[i] = new_px;

        source++;

    }

    ret->data = buffer;

    return ret;

}

/**
 * 
 * Reads 32 pixels and converts them into an unsigned integer mask
 * 
 * Example:
 * 
 * If we have the pixels 1 6 7 10 and the threshold is 5 the resulting 4 bits will be
 * 
 * 0 1 1 1
 * 
 * 
 */
unsigned int ConvertToBit(int pixels[])
{

    // We have a "clean" bit, meant only for shifting purposes
    unsigned int bit = 1;       // 0000 0000 0000 0000 ...(x7) ... 0000 0000 0000 0001

    // And the mask which we will return
    unsigned int mask = 0;      // 0000 0000 0000 0000 ...(x8)


    // We'll parse an image to bitmap 32 pixels at the time
    for (int i = 0; i < 32; i++)
    {

        if (pixels[i] >= 128)
        {
            // Big Endian Notation for better readibility of the BitMap
            bit = bit << (31 - i);
        }
        else
        {
            bit = 0;
        }

        mask = mask ^ bit;

        // Cleaning the bit
        bit = 1;
        
        
    }
    
    return mask;

}


/**
 * 
 * Straight-forward memory allocation. However, maybe it would be a good idea to associate each pointer with
 * another pointer to the end of the array.
 * 
 */
int * CreateBitMat(int rows, int cols)
{

    // Allocate enough memory for rows * cols pixels
    int * tmp = (int *)malloc((rows * cols) / 32);

    return tmp;
}


/**
 * 
 * Loading a BMP file
 * 
 */
int * LoadBitMatFromFile(char * name)
{

    FILE *fp = fopen(name, "rb");
    char buff[16];
    
    // Reading the image format
    if (!fgets(buff, sizeof(buff), fp)) {
        exit(1);
    }

    // Checking the image format
    if (buff[0] != 'P' || buff[1] != '4') {
         fprintf(stderr, "Invalid image format (must be 'P4')\n");
         exit(1);
    }

    int x, y, max_bright;
    
    fscanf(fp, "%d", &x);
    fscanf(fp, "%d", &y);
    fscanf(fp, "%d", &max_bright);


    int *tmp = CreateBitMat(x, y);
    fread(tmp, x, y, fp);

    return tmp;
}


/**
 * 
 * Save a BitMap to a File
 * 
 */
void SaveBitMatOnFile(unsigned int *mat, char *name, int size)
{

    FILE *fp = fopen(name, "wb");
    int resto;
    int ret[32];
    int j = 31;
    unsigned int * copy = mat;

    fprintf(fp, "P4\n");
    fprintf(fp, "%d %d\n", 512, 512);

    printf("fixe\n\n");
    for (int i = 0; i < size; i++)
    {


        for (int r = 0; r < 32; r++)
        {
            ret[r] = 0;
        }
        

        while(*copy > 0)
        {

            resto = *copy % 2;
            *copy = *copy / 2;
            ret[j] = resto;
            j--;

        }

        j = 31;

        for (int r = 0; r < 32; r++)
        {
            fprintf(fp,"%d", ret[r]);
        }

        copy++;

    }

    fclose(fp);


}

/**
 * 
 * Function that prints a BitMap matrix
 * 
 */
void PrintBitMat(unsigned int * bmp, int size)
{

    unsigned int * copy = bmp;

    for (int i = 0; i < size; i++)
    {
        Print32Bits(*copy);
        copy++;
    }
    

}


/**
 * 
 * Convert an integer to its binary form and print it
 * 
 */
void Print32Bits(int num)
{
    int resto;
    int ret[32];
    int j = 31;

    for (int i = 0; i < 32; i++)
    {
        ret[i] = 0;
    }
    

    while(num > 0)
    {

        resto = num % 2;
        num = num / 2;
        ret[j] = resto;
        j--;

    }

    for (int i = 0; i < 32; i++)
    {
        printf("%d", ret[i]);
    }

}


/**
 * 
 * Printing 32 Bits onto a file, following the same logic above
 * 
 */
void Print32BitsToFile(int num, char * name)
{

    int resto;
    int ret[32];
    int j = 31;

    FILE *fp = fopen(name, "wb");

    for (int i = 0; i < 32; i++)
    {
        ret[i] = 0;
    }
    

    while(num > 0)
    {

        resto = num % 2;
        num = num / 2;
        ret[j] = resto;
        j--;

    }

    for (int i = 0; i < 32; i++)
    {
        fprintf(fp,"%d", ret[i]);
    }

    fclose(fp);


}

