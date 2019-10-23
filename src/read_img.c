#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "../lib/formats.h"

int main(void)
{   
    DynamicMatrix *dm = LoadFromFile("lena.ppm");
    PrintMat(dm);

    SaveOnFile(dm, "saved_lena.ppm");

    PrintRGBPx(&(dm->data[241]));
    GreyMatrix * grey = ConvertToGreyscale(dm);

    PrintGreyMat(grey);
    SaveGreyOnFile(grey, "grey_lena.pgm");

    return 0;
}