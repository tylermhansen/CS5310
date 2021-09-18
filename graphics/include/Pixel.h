/*
A simple C Image API
Author: Tyler Hansen
CS5310 @ Roux Institute Fall 2021
*/

#ifndef PIXEL_H

#define PIXEL_H

// Image API Structures:
typedef struct {
    /* 
    FPixel
    --------------------------
    The FPixel structure describes a single pixel. Includes an array of three floats for the RGB value. Depth and Alpha values are stored for each pixel separately as part of the Image data structure.
    */
    float rgb[3];
} FPixel;

#endif