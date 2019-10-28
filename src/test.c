/** \mainpage <h1>pimg - Image Processing software</h1>
 * 
 * pimg is a C-based, simple project that allows a user the manipulate images that respect
 * the PNM format, i. e., RGB images in .ppm, Greyscale images in .pgm and managing BitMap
 * images. <br>
 * 
 * Core functionalities of the app include: structures that support the internal storage RGB,
 * Greyscale and Binary Matrixes with the use of the structures RGBPx and GPx. Each of the matrixes
 * has file compatibility, i. e., can be saved to and loaded from files, supports individual
 * pixel access and ROI access. It is worth mentioning that the ROI functionality is only
 * supported for cropping squares from images.
 * 
 * Furthermore, pimg also allows the user to convert from RGB to Greyscale and from Greyscale
 * to Binary with a user given threshold. However, the Binary implementation is merely a 
 * Greyscale image in which every GPx has a grey component of either 0 or 255. In future 
 * versions, Binary to file compability is a must.
 * 
 * There is also the option to apply a few filters to an RGB or Greyscale image. These include:<ul>
 * <li>Increasing or decreasing the brightness;</li>
 * <li>A user defined kernel filter, which in turn means the user can choose to blur, sharpen or
 * detect edges when using the proper kernel;</li>
 * <li>Watermarking a picture, however, this feature allows only a user to apply a watermark
 * that is already smaller than the picture to be watermarked</li>
 * </ul>
 * 
 * Features yet to be included in future versions:<ul>
 * <li>Filtering rectangle images</li>
 * <li>Read from and write to .pbm files</li>
 * <li>Resizing watermarks</li>
 * </ul>
 * 
 * 
 * \authors João Nogueira, Tiago Melo
 * 
 * 
 * 
 */



/*!
 * 
 * \file test.c
 * <h2>Test module</h2>
 * Driver code for testing every function developed on lena.ppm
 * 
 * 
 * @param Authors João Nogueira, Tiago Melo
 * 
 */


/**
 *  
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "../lib/filters.h"
#include "../lib/rgb.h"
#include "../lib/grey.h"
#include "../lib/bit.h"

#define AVERAGE -1
#define NONE 0
#define RED 1
#define GREEN 2
#define BLUE 3


int main(void)
{   

    /*
       *******************
     Testing Basic Functions 
       *******************
    */

    // Loading original image in RBG
    DynamicMatrix *dm = LoadFromFile("../res/lena.ppm");

    // Saving it on a different file
    SaveOnFile(dm, "../res/savedRGB.ppm");


    // Converting the original RGB image to Greyscale in each of the color channels
    // and storing the results (NONE means default RGB-Greyscale conversion)
    GreyMatrix * grey = ConvertToGreyscale(dm, NONE);
    SaveGreyOnFile(grey, "../res/grey_lena.pgm");

    GreyMatrix * red = ConvertToGreyscale(dm, RED);
    SaveGreyOnFile(red, "../res/red_lena.pgm");

    GreyMatrix * green = ConvertToGreyscale(dm, GREEN);
    SaveGreyOnFile(green, "../res/green_lena.pgm");

    GreyMatrix * blue = ConvertToGreyscale(dm, BLUE);
    SaveGreyOnFile(blue, "../res/blue_lena.pgm");


    // Loading GreyScale image
    GreyMatrix * gm = LoadGreyFromFile("../res/grey_lena.pgm");
    // Saving it on a different file
    SaveGreyOnFile(gm, "../res/savedGrey.pgm");


    // Accessing a single pixel in RGB format
    PrintRGBPx(AccessRGBPx(dm, 12, 12));
    printf("\n");

    // Accessing a RGB Matrix ROI and saving it (cropping an image)
    DynamicMatrix * sub = AccessRegion(dm, 0, 0, 420, 200);
    // PrintMat(sub);
    SaveOnFile(sub, "../res/cropped_lena.ppm");


    // Accessing a Grey Matrix ROI and saving it (cropping an image)
    GreyMatrix * grey_sub = AccessGreyRegion(gm, 80, 100, 320, 400);
    // PrintMat(sub);
    SaveGreyOnFile(grey_sub, "../res/cropped_grey_lena.pgm");


    // Converting a Greyscale image to "Bitmap", according to a given threshold
    int threshold = 100;
    GreyMatrix * bmp = ConvertToBitGreyMat(gm, threshold);
    // PrintGreyMat(bmp);
    SaveGreyOnFile(bmp, "../res/bit_lena.pgm");


    /*
       **********
     Testing Filters 
       **********
    */

    // Saturation


    DynamicMatrix * arial = LoadFromFile("../res/arial.ppm");
    DynamicMatrix * saturated = Saturate(arial, -100);
    SaveOnFile(saturated, "../res/saturated_arial.ppm");
    // PrintMat(saturated);


    GreyMatrix * saturated_grey = SaturateGrey(gm, 100);
    SaveGreyOnFile(saturated_grey, "../res/saturated_lena_grey.pgm");


    // Filtering: edge detection, blur and averaging

    // Edge detection Kernel
    int edge_detection[9] = {
                        -1, -1, -1,
                        -1, 8, -1,
                        -1, -1, -1
                    };

    // Blur Kernel
    int blur[9] = {
                        1, 1, 1,
                        1, 1, 1,
                        1, 1, 1
                    };

    DynamicMatrix * edge = FilterRGB(dm, edge_detection, 9);
    SaveOnFile(edge, "../res/edge_detection_lena.ppm");

    DynamicMatrix * blurred = FilterRGB(dm, blur, 9);
    SaveOnFile(blurred, "../res/blurry_lena.ppm");

    GreyMatrix * filtered = FilterGrey(gm, edge_detection, AVERAGE);
    SaveGreyOnFile(filtered, "../res/averaged_lena.pgm");


    // Watermarking

    // RGB
    DynamicMatrix * peppers = LoadFromFile("../res/peppers.ppm");
    DynamicMatrix * chopped_peppers = AccessRegion(peppers, 100, 120, 375, 400);
    SaveOnFile(chopped_peppers, "../res/chopped_peppers.ppm");

    DynamicMatrix * watered_peppers = WatermarkRGB(dm, chopped_peppers, 120, 120);
    SaveOnFile(watered_peppers, "../res/watermarked_peppers.ppm");

    // Greyscale
    DynamicMatrix * rgb_girl = LoadFromFile("../res/girl.ppm");
    GreyMatrix * girl = ConvertToGreyscale(rgb_girl, NONE);
    GreyMatrix * cropped_girl = AccessGreyRegion(girl, 0, 0, 255, 255);
    SaveGreyOnFile(cropped_girl, "../res/cropped_grey_girl.pgm");

    GreyMatrix * watermarked = WatermarkGrey(gm, cropped_girl, 120, 120);
    SaveGreyOnFile(watermarked, "../res/watermarked_lena.pgm");


    return 0;
}