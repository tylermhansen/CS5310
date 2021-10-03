/*
A simple C Image API
Author: Tyler Hansen
CS5310 @ Roux Institute Fall 2021
*/

#ifndef IMAGE_H

#define IMAGEH

// Include Dependencies
#include "Pixel.h"
#include "Color.h"
#include "ppmIO.h"

// Struct Definitions
typedef struct
{
    /* 
    Image
    --------------------------
    The Image structure describes an entire image made up of FPixels, which are stored as a one dimensional array.
    */
    FPixel *data;
    int rows; 
    int cols;
    float *depth; 
    float *alpha;
} Image;

// Constructors & Destructors:
Image *image_create(int rows, int cols);

void image_free(Image *src);

void image_init(Image *src);

int image_alloc(Image *src, int rows, int cols); 

void image_dealloc(Image*src);

// I/O Functions: 
Image *image_read(char *filename);

int image_write(Image *src, char *filename);

// Accesors: 
inline FPixel image_getf(Image *src, int r, int c){ return src->data[(r * src->cols) + c]; }

inline float image_getc(Image *src, int r, int c, int b){ return src->data[r * src->cols + c].rgb[b]; }

inline float image_geta(Image *src, int r, int c){ return src->alpha[(r * src->cols) + c]; }

inline float image_getz(Image *src, int r, int c){ return src->depth[(r * src->cols) + c]; }

inline void image_setf(Image *src, int r, int c, FPixel val){ src->data[(r * src->cols) + c] = val; }

inline void image_setc(Image *src, int r, int c, int b, float val){ src->data[(r * src->cols) + c].rgb[b] = val; }

inline void image_seta(Image *src, int r, int c, float val){ src->alpha[(r * src->cols) + c] = val; }

inline void image_setz(Image *src, int r, int c, float val){ src->depth[(r * src->cols) + c] = val; }

inline void image_setColor(Image *src, int r, int c, Color val){ src->data[r * src->cols + c].rgb[0] = val.c[0]; src->data[r * src->cols + c].rgb[1] = val.c[1]; src->data[r * src->cols + c].rgb[2] = val.c[2]; }

inline Color image_getColor(Image *src, int r, int c){ return (Color){{*src->data[(r * src->cols) + c].rgb}}; }

// Utility
void image_reset(Image *src);

void image_fill(Image *src, FPixel val);

void image_fillrgb(Image *src, float r, float g, float b);

void image_filla(Image *src, float a); 

void image_fillz(Image *src, float z);

#endif