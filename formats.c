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
#include "formats.h"
#include <stdlib.h>
#include <stdio.h>


DynamicMatrix * CreateMat(int rows, int cols)
{
    DynamicMatrix *tmp;

    tmp = (DynamicMatrix*)malloc(sizeof(DynamicMatrix));
    tmp->n = 0;

    tmp->x = rows;
    tmp->y = cols;
    
    tmp->size = rows*cols;

    tmp->data = (RGBPx *)calloc(tmp->size, sizeof(int));

    return tmp;
}

DynamicMatrix * LoadFromFile(char *name)
{
    FILE *fp = fopen(name, "rb");
    char buff[16];
    
    //read image format
    if (!fgets(buff, sizeof(buff), fp)) {
        exit(1);
    }

    //check the image format
    if (buff[0] != 'P' || buff[1] != '6') {
         fprintf(stderr, "Invalid image format (must be 'P6')\n");
         exit(1);
    }

    int x, y, max_bright;
    
    fscanf(fp, "%d", &x);
    fscanf(fp, "%d", &y);
    fscanf(fp, "%d", &max_bright);

    printf("%d %d\n", x, y);

    DynamicMatrix *tmp = CreateMat(x, y);
    fread(tmp->data, 3 * tmp->x, tmp->y, fp);

    return tmp;
}

void SaveOnFile(DynamicMatrix *dm, char *name)
{
    FILE *fp = fopen(name, "wb");

    fwrite(&(dm->n), sizeof(int), 1, fp);

    fwrite(dm->data, sizeof(int), dm->n, fp);
}

void PrintMat(DynamicMatrix *dm)
{

    RGBPx * array_ptr = dm->data;

    for(int i = 0; i <= dm->size; i++){
        PrintRGBPx(array_ptr);
        array_ptr++;
    }

    printf("\n");
}

void PrintRGBPx(RGBPx *px){

    printf("[ %d, %d, %d ]", px->r, px->g, px->b);

}