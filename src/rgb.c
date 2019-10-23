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
 * @param Authors João Nogueira, Tiago Melo
 * 
 */
#include "../lib/rgb.h"
#include "grey.c"
#include <stdlib.h>
#include <stdio.h>


DynamicMatrix * CreateRGBMat(int rows, int cols, int max_bright)
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

DynamicMatrix * LoadRGBFromFile(char *name)
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

    printf("%d %d\n", x, y);

    DynamicMatrix *tmp = CreateRGBMat(x, y, max_bright);
    fread(tmp->data, 3 * tmp->x, tmp->y, fp);

    return tmp;
}

void SaveRGBOnFile(DynamicMatrix *dm, char *name)
{
    FILE *fp = fopen(name, "wb");

    // Writing the image format
    fprintf(fp, "P6\n");

    // Writing rows, columns and maximum brightness
    fprintf(fp, "%d %d\n", dm->x, dm->y);
    fprintf(fp, "%d", dm->max_bright);

    // Writing data
    fwrite(dm->data, 3 * dm->x, dm->y, fp);
}

void PrintRGBMat(DynamicMatrix *dm)
{

    RGBPx * array_ptr = dm->data;

    for(int i = 0; i <= dm->size; i++){
        PrintRGBPx(array_ptr);
        array_ptr++;
    }

    printf("\n");
}

// RGBPx * GetPxAt(DynamicMatrix *dm, int index){ // Not working?
//     return &(dm->data[index]);
// }

void PrintRGBPx(RGBPx *px){
    printf("[ %d, %d, %d ]", px->r, px->g, px->b);
}


GreyMatrix * ConvertToGreyscale(DynamicMatrix *dm){

    GreyMatrix * ret = CreateGREYMat(dm->x, dm->y, dm->max_bright);
    RGBPx *source = dm->data;
    GPx *target = ret->data;

    for (int i = 0; i < dm->size; i++)
    {
        target = Greyscale(source);
        source++;
        target++;
    }


    return ret;
    
}

GPx * Greyscale(RGBPx * px){
    GPx * tmp = (GPx *)calloc(1, sizeof(RGBPx));
    tmp->grey = (px->r + px->g + px->b) / 3;

    return tmp;
}