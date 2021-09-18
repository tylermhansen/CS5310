/*
A simple C Image API
Author: Tyler Hansen
CS5310 @ Roux Institute Fall 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Image.h"
#include <math.h>

#define USECPP 0 // For use with PPM I/O Functions.

// Constructors & Destructors:

Image *image_create(int rows, int cols)
{
    /*
    Allocates an Image structure and initializes the top level fields to appropriate values. 
    Allocates space for an image of the specified size, unless either rows or cols is 0. 
    Returns a pointer to the allocated Image structure, or a NULL pointer if the operation fails.
    */
    printf("Creating image...\n");
    if( rows == 0 || cols == 0)
    {
        return NULL;
    }
    Image* src = malloc(sizeof(Image));
    src->rows = 0;
    src->cols = 0;
    if(image_alloc(src, rows, cols) != 0)
    {
        printf("image_alloc returned 0");
        return NULL;
    }
    return src;
}

void image_free(Image *src)
{
    /*
    De-allocates image data and frees the Image structure, ensuring no memory leaks.
    */
    free(src->data);
    free(src->alpha);
    free(src->depth);
    free(src);
}

void image_init(Image *src)
{
    /*
    Given an uninitialized Image structure, sets the rows and cols fields to zero and the data field to NULL.
    */
    src->rows = 0;
    src->cols = 0;
    src->data = NULL;
}

int image_alloc(Image *src, int rows, int cols)
{
    /*
    Allocates space for the image data given rows and columns and initializes the image data to appropriate 
    values, such as 0.0 for RGB and 1.0 for A and Z. Returns 0 if the operation is successful. Returns a non-zero 
    value if the operation fails. This function frees existing memory if rows and cols are both non-zero.
    */
    printf("Allocating Image...\n");
    if(src->rows != 0 && src->cols != 0)
    {
        free(src->data);
        free(src->alpha);
        free(src->depth);
    }
    src->rows = rows;
    src->cols = cols;

    src->data = malloc(sizeof(FPixel) * (rows * cols));
    src->alpha = malloc(sizeof(float*) * (rows * cols));
    src->depth = malloc(sizeof(float*) * (rows * cols));

    image_fillrgb(src, 0, 0, 0);
    image_filla(src, 1.0);
    image_fillz(src, 1.0);

    if ((!src->data || !src->alpha || !src->depth) && (rows && cols))
    {
        printf("image_alloc failed to allocate space for an image.");
        return -1;
    }
    
    return 0;
}

void image_dealloc(Image *src)
{
    /*
    De-allocates image data and resets the Image structure fields. The function does not free the Image structure.
    */
    free(src->data);
    free(src->alpha);
    free(src->depth);
    src->rows = 0; 
    src->cols = 0;
}

// I/O Functions:
Image *image_read(char *filename)
{
    /*
    Reads a PPM image from the given filename.Initializes the alpha channel to 1.0 and the z channel to 1.0. Returns a NULL pointer if the
    operation fails.

    Adapted Bruce Maxwell's "ppmIO.h" library, which defined a Pixel struct that was different from our FPixel.
    */
   printf("Reading image %s\n", filename);
   Pixel *image;
   int rows, cols, colors;

   image = readPPM(&rows, &cols, &colors, filename);

   if (!image)
   {
       fprintf(stderr, "Unable to read %s\n", filename);
       exit(-1);
   }
   Image *src = image_create(rows, cols);
   for (int i = 0; i < rows * cols; i++){
       src->data[i].rgb[0] = (float)(image[i].r);
       src->data[i].rgb[1] = (float)(image[i].g);
       src->data[i].rgb[2] = (float)(image[i].b);
   }
   return src;
}

int image_write(Image *src, char *filename)
{
    printf("Writing image %s\n", filename);
    if(!src || !filename)
    {
        return -1; 
    }
    Pixel* image = (Pixel *)malloc(sizeof(Pixel)* (src->rows) * (src->cols));
    for (int i = 0; i < src->rows * src->cols; i++){
       image[i].r = (unsigned char)trunc(src->data[i].rgb[0]);
       image[i].g = (unsigned char)trunc(src->data[i].rgb[1]);
       image[i].b = (unsigned char)trunc(src->data[i].rgb[2]);
   }
    writePPM(image, src->rows, src->cols, 255, filename);
    return 0;
}

// Utility:

void image_fillrgb(Image *src, float r, float g, float b)
{
    for (int i = 0; i < (src->rows) * (src->cols); i++)
    {
        src->data[i].rgb[0] = r;
        src->data[i].rgb[1] = g;
        src->data[i].rgb[2] = b;
    }
}

void image_filla(Image *src, float a)
{
    for (int i = 0; i < src->rows * src->cols; i++)
    {
        src->alpha[i] = a;
    }
}

void image_fillz(Image *src, float z)
{
    for (int i = 0; i < src->rows * src->cols; i++)
    {
        src->depth[i] = z;
    }
}
