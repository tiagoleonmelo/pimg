#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "formats.h"

// int main(void)
// {
//     FILE * fp;
//     char * line = NULL;
//     size_t len = 0;
//     ssize_t read;

//     fp = fopen("lena.ppm", "r");
//     if (fp == NULL)
//         exit(EXIT_FAILURE);

//     while ((read = getline(&line, &len, fp)) != -1) {
//         printf("Retrieved line of length %zu:\n", read);
//         printf("%s", line);
//     }

//     fclose(fp);
//     if (line)
//         free(line);
//     exit(EXIT_SUCCESS);
// }

int main(void)
{   
    DynamicMatrix *dm = LoadFromFile("lena.ppm");
    PrintMat(dm);
    return 0;
}