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

    GPx buffer[gm->size];
    GreyMatrix * ret = CreateGreyMat(gm->x, gm->y);
    GPx * source = gm->data;
    GPx new_px;

    int kernel[9] = {
                        -1, -1, -1,
                        -1, 8, -1,
                        -1, -1, -1
                    };

    int x, y;
    int new_grey = 0;
    int counter = 0;

    // for(int i = 0; i < gm->size; i++)
    // {

    //     x = i / gm->x;
    //     y = i % gm->y;


    //     for(int g = -1; g < 2; g++)
    //     {
    //         for(int f = -1; f < 2; f++)
    //         {

    //             if ((x + f) < 0 || (x + f) > gm->x || (y + g) < 0 || (y + g) > gm->y)
    //             {
    //                 new_px->grey += 255;
    //             }
    //             else
    //             {
    //                 new_px->grey += kernel[counter] * source[((x+g) * gm->x) + (y+f)].grey;
    //                 // printf("OLOLOL\n");

    //             }

    //             counter++;
    //             // printf("COUNTER %d\n", counter);
   
    //         }
            
    //     }

    //     new_px->grey /= 10;

    //     // new_px->grey = (unsigned char) new_grey;


    //     buffer[i] = *new_px;
    //     // printf("%d : %d,", i, new_grey);

    //     source++;
    //     new_grey = 0;
    //     counter = 0;
    // }

    for(int i = 0; i < gm->size; i++)
    {
        
        new_px = *source;
        x = i / gm->x;
        y = i % gm->y;
        
        buffer[i] = new_px;

        source++;
    }

    // buffer = gm -> data;
    ret->data = buffer;

    return ret;

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
// GPx PxAverage(int idx_center, GreyMatrix * gm, int kernel_side)
// {

//     int kernel_size = kernel_side*kernel_side;
   
//     int x = idx_center / gm->x;
//     int y = idx_center % gm->y;

//     // (x,y) is now the center of our kernel
//     // Now we just need to spin around it

//     // Coordinates of a start pixel inside the kernel (top left)
//     // and end pixel (bottom right)
//     int x_start, y_start;
//     int x_end, y_end;

//     x_start = x - kernel_side/2;
//     y_start = y - kernel_side/2;

//     x_end = x + kernel_side/2;
//     y_end = y + kernel_side/2;

//     int target_idx;

//     GreyMatrix * kernel = AccessGreyRegion(gm, x_start, y_start, x_end, y_end);

//     // Buffer that will be used later to calculate the average of grey colors
//     GPx * buffer = malloc(kernel_size * sizeof(GPx));

//     for(int i = 0; i < kernel_size; i++)
//     {


//         buffer[i] = gm->data[target_idx];

//     }

// }

