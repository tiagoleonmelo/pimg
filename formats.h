typedef struct{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB;


// Move these to a different module
// typedef struct{
//     int y;
// } Greyscale;

// typedef struct{
//     int byte[8]; 
// } Byte;

typedef struct{
    int height;
    int length;
    RGB matrix[0][0];    // Starting our matrix with dummy values
                            // memory will be allocated later
} Imagem;