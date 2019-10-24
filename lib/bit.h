/**
 * 
 * Header that contains DynMat functions for the Bit Module
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

int *  CreateBitMat(int rows, int cols);

int * LoadBitMatFromFile(char *);

void SaveBitMatOnFile(unsigned int *mat, char *name, int size);

void PrintBitMat(unsigned int *mat, int size);

void PrintBit(int index);

void Print32Bits(int n);

void Print32BitsToFile(int num, char *);




#endif //INC_00_BIT_H