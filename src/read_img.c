#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "../lib/formats.h"

#define NONE 0
#define RED 1
#define GREEN 2
#define BLUE 3


int main(void)
{   

    // Loading, printing and saving an image in RGB
    DynamicMatrix *dm = LoadFromFile("../res/lena.ppm");
    // PrintMat(dm);
    SaveOnFile(dm, "../res/saved_lena.ppm");

    // Loading, printing and saving an image in Greyscale
    GreyMatrix * gm = LoadGreyFromFile("../res/grey_lena.pgm");
    // PrintGreyMat(gm);
    SaveGreyOnFile(gm, "../res/loaded.pgm");


    // Accessing a single pixel in RGB format
    PrintRGBPx(AccessRGBPx(dm, 501, 499));
    printf("\n");


    // Accessing a RGB Matrix Region
    DynamicMatrix * sub = AccessRegion(dm, 0, 0, 512, 512);
    // PrintMat(sub);
    SaveOnFile(sub, "../res/cropped_lena.ppm");
    

    // Converting an RGB image to greyscale in each of the color channels
    // and storing the results (NONE means default RGB-Greyscale conversion)
    GreyMatrix * grey = ConvertToGreyscale(dm, NONE);
    GreyMatrix * red = ConvertToGreyscale(dm, RED);
    GreyMatrix * green = ConvertToGreyscale(dm, GREEN);
    GreyMatrix * blue = ConvertToGreyscale(dm, BLUE);

    SaveGreyOnFile(grey, "../res/grey_lena.pgm");
    SaveGreyOnFile(red, "../res/red_lena.pgm");
    SaveGreyOnFile(green, "../res/green_lena.pgm");
    SaveGreyOnFile(blue, "../res/blue_lena.pgm");



    return 0;
}