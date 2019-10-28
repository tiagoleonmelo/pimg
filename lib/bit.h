/**
 * 
 * \file bit.h
 * Header which contains the required structures and function declarations for the Bit Module.
 *
 */

#ifndef INC_00_BIT_H
#define INC_00_BIT_H

/**
 * 
 * Data structure
 * 
 */
typedef struct{
    unsigned int bit : 1; 
} Bit;

/**
 * 
 * BIT Matrix that can grow dynamically, based on the provided
 * MyVec implementation.
 * 
 */
typedef struct {
    Bit *data;
    int x, y;
    int size;
} BitMatrix;

/**
 * 
 * Structure that holds the whole image. For each black pixel found,
 * image will store it using masks. The image can later be loading with a
 * XOR operation
 * 
 */
typedef struct{
    unsigned long long image; 
} BitMap;

// Bit Functions

//read/write
int *  CreateBitMat(int rows, int cols);

int * LoadBitMatFromFile(char *);

void SaveBitMatOnFile(unsigned int *mat, char *name, int size);

void PrintBitMat(unsigned int *mat, int size);

//pixel/area
void PrintBit(int index);

void Print32Bits(int n);

void Print32BitsToFile(int num, char *);

//returntype * AccessBitRegion(matrixtype *dm, int x1, int y1, int x2, int y2);




#endif //INC_00_BIT_H