/**
 * 
 * <h2>Bit Image Manipulation</h2>
 * <br>
 * The Bit module contains methods for reading and writing bitmap images.
 * <br>
 * It is worth mentioning that a Binary Image is internally saved as a Greyscale Image, and is
 * only converted to binary when reading from or writing to files. This way we can more easily
 * increase compatibility between modules and image access.
 * <br>
 * At the time of writing, the feature of reading and writing .pbm files is not yet implemented.
 * Instead, everything is treated as .pgm. Ideally, this would be implemented, but right now
 * it's just TODO:.
 * <br>
 * Some attempts were made to implement a way to internally save Bitmaps, namely, an integer 
 * array, in which each item would store 32 bits, resulting in an array of masks. This was not
 * the option chosen, yet, the methods were not deleted and there is available documentation for
 * each of them.
 * <br>
 * <b>In short</b>, binary image saving and loading were done with the Greyscale module. This module
 * would be useful in possible future versions.
 * <br>
 * @param Authors João Nogueira, Tiago Melo
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "../lib/bit.h"

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
 * Iterate over an array of masks and every 32 pixels processed, de-mask the integer and
 * save it to a .pbm file.
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
 * Prints a BitMap matrix @arg bmp of size @arg size
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