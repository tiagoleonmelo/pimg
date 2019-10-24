/**
 * 
 * Filters module.
 * 
 * Contains the implementation of the available functions to manipulate image data
 * 
 * @param Authors João Nogueira, Tiago Melo
 * 
 */
#include "../lib/formats.h"
#include "../lib/filters.h"
#include <stdlib.h>
#include <stdio.h>

#define NONE 0
#define RED 1
#define GREEN 2
#define BLUE 3

DynamicMatrix * Saturate(DynamicMatrix * dm)
{

    RGBPx * ptr = dm->data;
    DynamicMatrix * ret = CreateMat(dm->x, dm->y, dm->max_bright);
    RGBPx *buffer = malloc(dm->size * sizeof(RGBPx));
    RGBPx new_px;
    int value = 20;

    for(int i = 0; i < dm->size; i++)
    {

        new_px = *(ptr);

        new_px.r += value;
        if (new_px.r > 255)
        {
            new_px.r = 255;
        }
        
        new_px.g += value;
        if (new_px.g > 255)
        {
            new_px.g = 255;
        }
        
        new_px.b += value;
        if (new_px.b > 255)
        {
            new_px.b = 255;
        }
        buffer[i] = new_px;

        ptr++;

    }

    ret->data = buffer;

    return ret;
}


