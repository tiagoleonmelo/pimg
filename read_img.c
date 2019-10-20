#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "formats.h"

int main(void)
{   
    DynamicMatrix *dm = LoadFromFile("lena.ppm");
    PrintMat(dm);
    return 0;
}