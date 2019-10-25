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

/**
 * 
 * Manipulating brightness levels for RGB Images
 * 
 */
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

/**
 * 
 * Manipulating brightness levels for Greyscale Images
 * 
 */
GreyMatrix * SaturateGrey(GreyMatrix * dm, int value)
{

    GPx * ptr = dm->data;
    GreyMatrix * ret = CreateGreyMat(dm->x, dm->y);
    GPx *buffer = malloc(dm->size * sizeof(GPx));
    GPx new_px;
    int test = 0;

    for(int i = 0; i < dm->size; i++)
    {

        new_px = *(ptr);


        test = new_px.grey + value;

        if (test > 255)
        {
            new_px.grey = 255;
        }
        else if (test < 0)
        {
            new_px.grey = 0;
        }   
        else
        {
            new_px.grey += value;
        }
        
        
        buffer[i] = new_px;

        ptr++;

    }

    ret->data = buffer;

    return ret;
}





GreyMatrix * Filter(GreyMatrix * gm, int kernel_side)
{

    // Allocating enough memory for a small matrix of side=kernel_side that will "absorb"
    // the gm's pixels
    GPx * buffer = malloc(kernel_side * kernel_side * sizeof(GPx));
    GreyMatrix * ret = CreateGreyMat(gm->x, gm->y);
    GPx * source = gm->data;

    for(int i = 0; i < gm->size; i++)
    {
        
        buffer[i] = PxAverage(i, gm, kernel_side);
        source++;
    }

    ret->data = buffer;

}


/**
 * 
 * We know the center of the kernel
 * 
 * Convert it to coordinates using the D=Q*d+R formula
 * 
 * Knowing the size of the side of the square of the kernel we can access every px we want
 * 
 * Accessing every pixel we want we can now calculate the average and return it
 * 
 */
GPx PxAverage(int idx_center, GreyMatrix * gm, int kernel_side)
{

    int x = idx_center / gm->x;
    int y = idx_center % gm->y;
    int kernel_size = kernel_side*kernel_side;

    // (x,y) is now the center of our kernel
    // Now we just need to spin around it

    // Coordinates of a target pixel inside the kernel
    int x_target, y_target;
    int target_idx;

    // Buffer that will be used later to calculate the average of grey colors
    GPx * buffer = malloc(kernel_size * sizeof(GPx));

    for(int i = 0; i < kernel_size; i++)
    {


        buffer[i] = gm->data[target_idx];

    }

}

