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

    tmp->a = (int **)calloc(tmp->size, sizeof(int));

    return tmp;
}

DynamicMatrix * LoadFromFile(char *name)
{
    FILE *fp = fopen(name, "rb");

    int x, y;
    fread(&x, sizeof(int), 1, fp);
    fread(&y, sizeof(int), 1, fp);

    DynamicMatrix *tmp = CreateMat(x, y);
    fread(tmp->a, sizeof(int), tmp->size, fp);

    return tmp;
}

void SaveOnFile(DynamicMatrix *dm, char *name)
{
    FILE *fp = fopen(name, "wb");

    int n;
    fwrite(&(dm->n), sizeof(int), 1, fp);

    fwrite(dm->a, sizeof(int), dm->n, fp);
}