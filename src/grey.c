/**
 * 
 * \file <h2>GreyScale Image Manipulation</h2>
 * <br>
 * The GreyScale module contains methods for:<ul>
 * <li>reading</li>
 * <li>writing</li>
 * <li>converting GreyScale images to "Bitmap"</li>
 * </ul>
 * 
 * Like it was explained in the @file bit.c module, a Bitmap is saved internally through
 * usage of a Greyscale matrix. However, the methods developed when trying to implement another
 * option (array of masks) were kept and properly documented, given that they can still be used
 * in possible future versions.
 * 
 * @param Authors João Nogueira, Tiago Melo
 * 
 */

/**
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include "../lib/grey.h"

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
 * Load a Greyscale Matrix from a file called name
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
    fscanf(fp, "%d\n", &max_bright);


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
 * Access the position at [ @arg row][ @arg col] in the matrix @arg dm
 * 
 */
GPx * AccessGPx(GreyMatrix * dm, int row, int col){
    int index = row * dm->x + col;
    return &(dm->data[index]);
}


/**
 * 
 * Print a Greyscale Pixel @arg px, which is just the grey component of it
 * 
 */
void PrintGPx(GPx * px){
    printf("%d ", px->grey);
}


/**
 * 
 * Access a given ROI. Top left pixel is at ( @arg x1, @arg y1) and bottom right pixel is
 * at ( @arg x2, @arg y2). Returns the sub-matrix from @arg dm that follows these conditions.
 * 
 */
GreyMatrix * AccessGreyRegion(GreyMatrix *dm, int x1, int y1, int x2, int y2)
{

    int rows = x2 - x1+1;
    int cols = y2 - y1+1;
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

    GreyMatrix * sub = CreateGreyMat(rows, cols);
    GPx buffer[sub->size];

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

                    i+=jump-1;
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
                    i+=jump-1;
                    help = 0;
                }
            }

        sub->data = buffer;

    }
    

    return sub;
    
}


// Conversion Methods


/**
 * 
 * Option chosen: instead of saving the image using bits, save it in greymap,
 * where a 1 is replaced with 255 and a 0 replaced with 0.
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
 * 
 * Function that converts a Greyscale Matrix gm to a BitMap matrix
 * and returns it.
 * 
 * It iterates through Greyscale data, matches it with a user given threshold and
 * creates a Bit based on that operation.
 * 
 * An array of masks is then returned
 * 
 * This method is not used in the current implementation, however it can still be relevant
 * in a possible future version.
 * 
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

    
    return buffer;
    
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
 * This method is not used in the current implementation, however it can still be relevant
 * in a possible future version.
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