/**
 * 
 * 
 * Test module
 * 
 * 
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "../lib/filters.h"
#include "../lib/rgb.h"
#include "../lib/grey.h"
#include "../lib/bit.h"

#define NONE 0
#define RED 1
#define GREEN 2
#define BLUE 3


int main(void)
{   
    // Loading original image in RBG
    DynamicMatrix *dm = LoadFromFile("../res/lena.ppm");
    // Saving it on a different file
    SaveOnFile(dm, "../res/savedRGB.ppm");


    // Converting the original RGB image to greyscale in each of the color channels
    // and storing the results (NONE means default RGB-Greyscale conversion)
    GreyMatrix * grey = ConvertToGreyscale(dm, NONE);
    SaveGreyOnFile(grey, "../res/grey_lena.pgm");

    GreyMatrix * red = ConvertToGreyscale(dm, RED);
    SaveGreyOnFile(red, "../res/red_lena.pgm");

    GreyMatrix * green = ConvertToGreyscale(dm, GREEN);
    SaveGreyOnFile(green, "../res/green_lena.pgm");

    GreyMatrix * blue = ConvertToGreyscale(dm, BLUE);
    SaveGreyOnFile(blue, "../res/blue_lena.pgm");


    // Loading GreyScale image
    GreyMatrix * gm = LoadGreyFromFile("../res/grey_lena.pgm");
    // Saving it on a different file
    SaveGreyOnFile(gm, "../res/savedGrey.pgm");


    // Accessing a single pixel in RGB format
    PrintRGBPx(AccessRGBPx(dm, 511, 511));
    printf("\n");

    // Accessing a RGB Matrix Region
    DynamicMatrix * sub = AccessRegion(dm, 100, 100, 450, 450);
    // PrintMat(sub);
    SaveOnFile(sub, "../res/cropped_lena.ppm");


    // Accessing a Grey Matrix Region
    GreyMatrix * grey_sub = AccessGreyRegion(gm, 100, 100, 500, 500);
    // PrintMat(sub);
    SaveGreyOnFile(grey_sub, "../res/cropped_grey_lena.pgm");


    int threshold = 100;
    GreyMatrix * bmp = ConvertToBitGreyMat(gm, threshold);
    // PrintGreyMat(bmp);
    SaveGreyOnFile(bmp, "../res/bit_lena.pgm");


    DynamicMatrix * saturated = Saturate(dm, -100);
    SaveOnFile(saturated, "../res/saturated_lena.ppm");
    // PrintMat(saturated);


    GreyMatrix * saturated_grey = SaturateGrey(gm, 100);
    SaveGreyOnFile(saturated_grey, "../res/saturated_lena_grey.pgm");


    GreyMatrix * filtered = Filter(gm, 3);
    SaveGreyOnFile(filtered, "../res/filtered_lena.pgm");




    return 0;
}