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
    DynamicMatrix *dm = LoadFromFile("../res/lena.ppm");
    // PrintMat(dm);

    SaveOnFile(dm, "../res/saved_lena.ppm");

    PrintRGBPx(&(dm->data[241]));
    printf("\n");
    
    GreyMatrix * grey = ConvertToGreyscale(dm, NONE);
    GreyMatrix * red = ConvertToGreyscale(dm, RED);
    GreyMatrix * green = ConvertToGreyscale(dm, GREEN);
    GreyMatrix * blue = ConvertToGreyscale(dm, BLUE);

    // PrintGreyMat(grey);
    SaveGreyOnFile(grey, "../res/grey_lena.pgm");
    SaveGreyOnFile(red, "../res/red_lena.pgm");
    SaveGreyOnFile(green, "../res/green_lena.pgm");
    SaveGreyOnFile(blue, "../res/blue_lena.pgm");

    GreyMatrix * loaded = LoadGreyFromFile("../res/grey_lena.pgm");
    SaveGreyOnFile(loaded, "../res/loaded.pgm");

    return 0;
}