#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "formats.h"

int main(void)
{   
    DynamicMatrix *dm = LoadFromFile("lena.ppm");
    PrintMat(dm);
    SaveOnFile(dm, "saved_lena.ppm");
    PrintRGBPx(&(dm->data[241]));
    DynamicMatrix * grey = ConvertToGreyscale(dm);
    SaveOnFile(grey, "grey_lena.ppm");

    return 0;
}