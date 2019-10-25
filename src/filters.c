/**
 * 
 * Filters module.
 * 
 * Contains the implementation of the available functions to manipulate image data
 * 
 * @param Authors João Nogueira, Tiago Melo
 * 
 */
#include "../lib/rgb.h"
#include "../lib/grey.h"
#include "../lib/bit.h"
#include "../lib/filters.h"
#include <stdlib.h>
#include <stdio.h>

#define NONE 0
#define RED 1
#define GREEN 2
#define BLUE 3

DynamicMatrix * Saturate(DynamicMatrix * dm, int value)
{

    RGBPx * ptr = dm->data;
    DynamicMatrix * ret = CreateMat(dm->x, dm->y, dm->max_bright);
    RGBPx *buffer = malloc(dm->size * sizeof(RGBPx));
    RGBPx new_px;
    int test = 0;

    for(int i = 0; i < dm->size; i++)
    {

        new_px = *(ptr);


        test = new_px.r + value;

        if (test > 255)
        {
            new_px.r = 255;
        }
        else if (test < 0)
        {
            new_px.r = 0;
        }   
        else
        {
            new_px.r += value;
        }
        

        test = new_px.g + value;

        if (test > 255)
        {
            new_px.g = 255;
        }
        else if (test < 0)
        {
            new_px.g = 0;
        }
        else
        {
            new_px.g += value;
        }
        

        test = new_px.b + value;
  
        if (test > 255)
        {
            new_px.b = 255;
        }
        else if (test < 0)
        {
            new_px.b = 0;
        } 
        else
        {
            new_px.b += value;
        }
        
        buffer[i] = new_px;

        ptr++;

    }

    ret->data = buffer;

    return ret;
}


