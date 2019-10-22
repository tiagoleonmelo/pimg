/**
 * 
 * Header that contains DynMat functions for the Bit Module
 * 
 */

#ifndef INC_00_BIT_H
#define INC_00_BIT_H


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


#endif //INC_00_BIT_H