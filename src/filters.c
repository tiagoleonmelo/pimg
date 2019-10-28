/**
 * 
 * \file filters.c
 * <h2>Filters module</h2>
 * 
 * Contains the implementation of the available functions to manipulate image data, namely:<ul>
 * <li>Kernel Filters</li>
 * <li>Manipulating brightness</li>
 * <li>Watermarking</li>
 * 
 * It is worth mentioning these methods are only appliable to images that arent Bitmap (i. e.
 * RGB and Greyscale). The current implementation allows a user to pass a Bitmap-Greyscale image
 * as arguments but it simply doesn't work as it's meant to. 
 * 
 * @param Authors João Nogueira, Tiago Melo
 * 
 */

/**
 * 
 */
#include "../lib/rgb.h"
#include "../lib/grey.h"
#include "../lib/bit.h"
#include "../lib/filters.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define AVERAGE -1
#define NONE 0
#define RED 1
#define GREEN 2
#define BLUE 3

/**
 * 
 * Manipulating brightness levels for RGB Images
 * 
 *   value is added to each of the   dm pixels.
 * 
 * In this case, each channel of an RGB pixel is the result of this sum
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
 *   value is added to each of the   dm pixels.
 * 
 * In this case, each Greyscale pixel of the resulting matrix is the result of the sum between
 * the dm's pixel and value.
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




/**
 * 
 * Filter function
 * 
 * Applies a square kernel, of odd side, to the RGB image passed as   gm.
 *  
 *   kernel_size can assume a special value of -1 to apply an average filter to the whole image
 * It is worth mentioning that, in this case, the kernel simply assumes a 3x3 box. This option
 * was chosen given that a larger kernel would hinder the effects of the filter function.
 * 
 * However, a possible implementation that would allow variation of kernel sizes would be to
 * pass   kernel_size as a negative value and use the abs() of that value as the kernel size.
 * This way the user could pass a variable kernel to apply an average filter. We chose not to
 * do this.
 * 
 */
DynamicMatrix * FilterRGB(DynamicMatrix * gm, int kernel[], int kernel_size)
{

    // Checking if our kernel has the right dimensions (perfect square and odd number as side)
    if((kernel_size != AVERAGE) && (sqrt(kernel_size) != floor(sqrt(kernel_size)) || (int) sqrt(kernel_size) % 2 != 1))
    {
        printf("ERROR: Unsupported operation for the given Kernel, returning original matrix\n");
        return gm;
    }

    // If we get here, we can safely cast to int
    int kernel_side = (int) sqrt(kernel_size);

    // Getting up and lower bounds, with which we will apply our kernel to the image
    int up = kernel_side/2 + 1;
    int down = - kernel_side/2;

    if (kernel_size == AVERAGE)
    {
        up = 2;
        down = -1;
    }

    // Data fetching and storing variables
    RGBPx buffer[gm->size];
    DynamicMatrix * ret = CreateMat(gm->x, gm->y, gm->max_bright);
    RGBPx * source = gm->data;
    RGBPx *new_px = malloc(sizeof(RGBPx));

    // Tracking variables, useful for positions and counting
    int x, y;
    int new_red = 0;
    int new_green = 0;
    int new_blue = 0;
    int counter = 0;

    for(int i = 0; i < gm->size; i++)
    {

        x = i / gm->x;
        y = i % gm->y;


        for(int g = down; g < up; g++)
        {
            for(int f = down; f < up; f++)
            {

                if ((x + f) < 0 || (x + f) > gm->x || (y + g) < 0 || (y + g) > gm->y)
                {
                    new_red += 255;
                    new_green += 255;
                    new_blue += 255;
                }
                else
                {
                    if (kernel_size == AVERAGE)
                    {
                        new_red += gm->data[((x+g) * gm->x) + (y+f)].r;
                        new_green += gm->data[((x+g) * gm->x) + (y+f)].g;
                        new_blue += gm->data[((x+g) * gm->x) + (y+f)].b;
                    }
                    else
                    {
                        new_red += kernel[counter] * gm->data[((x+g) * gm->x) + (y+f)].r;
                        new_green += kernel[counter] * gm->data[((x+g) * gm->x) + (y+f)].g;
                        new_blue += kernel[counter] * gm->data[((x+g) * gm->x) + (y+f)].b;
                    }

                }

                counter++;
   
            }
            
        }

        new_px->r = new_red / kernel_size;
        new_px->g = new_green / kernel_size;
        new_px->b = new_blue / kernel_size;


        buffer[i] = *new_px;

        source++;
        new_red = 0;
        new_green = 0;
        new_blue = 0;
        counter = 0;
    }

    ret->data = buffer;

    return ret;

}


/**
 * 
 * Filter function
 * 
 * Applies a square kernel, of odd side, to the greyscale image passed as   gm.
 *  
 *   kernel_size can assume a special value of -1 to apply an average filter to the whole image
 * It is worth mentioning that, in this case, the kernel simply assumes a 3x3 box. This option
 * was chosen given that a larger kernel would hinder the effects of the filter function.
 * 
 * However, a possible implementation that would allow variation of kernel sizes would be to
 * pass   kernel_size as a negative value and use the abs() of that value as the kernel size.
 * This way the user could pass a variable kernel to apply an average filter. We chose not to
 * do this.
 * 
 */
GreyMatrix * FilterGrey(GreyMatrix * gm, int kernel[], int kernel_size)
{

    // Checking if our kernel has the right dimensions (perfect square and odd number as side)
    if((kernel_size != AVERAGE) && (sqrt(kernel_size) != floor(sqrt(kernel_size)) || (int) sqrt(kernel_size) % 2 != 1))
    {
        printf("ERROR: Unsupported operation for the given Kernel, returning original matrix\n");
        return gm;
    }


    // If we get here, we can safely cast to int
    int kernel_side = (int) sqrt(kernel_size);

    int up = kernel_side/2 + 1;
    int down = - kernel_side/2;

    // Getting up and lower bounds, with which we will apply our kernel to the image
    if (kernel_size == AVERAGE)
    {
        up = 2;
        down = -1;
    }

    

    // Data fetching and storing variables
    GPx buffer[gm->size];
    GreyMatrix * ret = CreateGreyMat(gm->x, gm->y);
    GPx * source = gm->data;
    GPx *new_px = malloc(sizeof(GPx));


    // Tracking variables, useful for positions and counting
    int x, y;
    int new_grey = 0;
    int counter = 0;

    for(int i = 0; i < gm->size; i++)
    {

        x = i / gm->x;
        y = i % gm->y;


        for(int g = down; g < up; g++)
        {
            for(int f = down; f < up; f++)
            {

                if ((x + f) < 0 || (x + f) > gm->x || (y + g) < 0 || (y + g) > gm->y)
                {
                    new_grey += 255;
                }
                else
                {
                    if (kernel_size == AVERAGE)
                    {
                        new_grey += gm->data[((x+g) * gm->x) + (y+f)].grey;
                    }
                    else
                    {
                        new_grey += kernel[counter] * gm->data[((x+g) * gm->x) + (y+f)].grey;
                    }
                }

                counter++;
   
            }
            
        }

        new_px->grey = new_grey / kernel_size;


        buffer[i] = *new_px;

        source++;
        new_grey = 0;
        counter = 0;
    }

    ret->data = buffer;

    return ret;

}



/**
 * 
 * Returns a watermarked version of the RGB image   gm 
 * with the watermark   watermark
 *  
 * Assumes watermark is already smaller than gm (doesn't support watermark resizing)
 * 
 * We could have done this with ROIs but, in our opinion, this way is simpler
 * 
 */
DynamicMatrix * WatermarkRGB(DynamicMatrix * gm, DynamicMatrix * watermark, int x_start, int y_start)
{

    DynamicMatrix * ret = CreateMat(gm->x, gm->y, gm->max_bright);

    RGBPx * img_source = gm->data;
    RGBPx * wm_source = watermark->data;
    RGBPx * buffer = malloc(ret->size * sizeof(GPx));

    RGBPx img_px, wm_px, result;

    int counter = 0;


    for(int i = 0; i < gm->size; i++)
    {

        // Checking if i is within the bounds of the ROI
        if(RGBChecker(gm, y_start, x_start, y_start + watermark->y + 1, x_start + watermark->x + 1, i))
        {

            img_px = img_source[i];
            wm_px = wm_source[counter];

            result.r = img_px.r * 0.65 + wm_px.r * 0.35;
            result.g = img_px.g * 0.65 + wm_px.g * 0.35;
            result.b = img_px.b * 0.65 + wm_px.b * 0.35;

            buffer[i] = result;

            counter++;

        }
        else
        {

            buffer[i] = img_source[i];

        }

    }


    ret->data = buffer;

    return ret;

}



/**
 * 
 * Returns a watermarked version of the Greyscale image   gm 
 * with the watermark   watermark
 *  
 * Assumes watermark is already smaller than gm (doesn't support watermark resizing)
 * 
 * We could have done this with ROIs but, in our opinion, this way is simpler
 * 
 */
GreyMatrix * WatermarkGrey(GreyMatrix * gm, GreyMatrix * watermark, int x_start, int y_start)
{

    GreyMatrix * ret = CreateGreyMat(gm->x, gm->y);

    GPx * img_source = gm->data;
    GPx * wm_source = watermark->data;
    GPx * buffer = malloc(ret->size * sizeof(GPx));

    GPx img_px, wm_px, result;

    int counter = 0;


    for(int i = 0; i < gm->size; i++)
    {

        // Checking if i is within the bounds of the ROI
        if(GreyChecker(gm, x_start, y_start, x_start + watermark->x + 1, y_start + watermark->y + 1, i))
        {

            img_px = img_source[i];
            wm_px = wm_source[counter];
            result.grey = img_px.grey * 0.65 + wm_px.grey * 0.35;

            buffer[i] = result;

            counter++;

        }
        else
        {

            buffer[i] = img_source[i];

        }

    }


    ret->data = buffer;

    return ret;

}


// Helper Functions

/**
 * 
 * Returns 1 if   i is between the bounds set by   x0   y0   x1   y1 and 0
 * if not in the matrix   gm
 * 
 */
int RGBChecker(DynamicMatrix * gm, int x0, int y0, int x1, int y1, int i)
{
    int x = i / gm->x;
    int y = i % gm->x;
    
    return (x0 < x) && (x < x1) && (y0 < y) && (y < y1);

}


/**
 * 
 * Returns 1 if   i is between the bounds set by   x0   y0   x1   y1 and 0
 * if not in the matrix   gm
 * 
 */
int GreyChecker(GreyMatrix * gm, int x0, int y0, int x1, int y1, int i)
{
    int x = i / gm->x;
    int y = i % gm->x;
    
    return (x0 < x) && (x < x1) && (y0 < y) && (y < y1);

}

