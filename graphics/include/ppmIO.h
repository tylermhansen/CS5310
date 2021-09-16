#ifndef PPMIO_H

#define PPMIO_H

#include "Pixel.h"

FPixel *readPPM(int *rows, int *cols, int * colors, char *filename);
void writePPM(FPixel *image, int rows, int cols, int colors, char *filename);

unsigned char *readPGM(int *rows, int *cols, int *intensities, char *filename);
void writePGM(unsigned char *image, long rows, long cols, int intensities, char *filename);

int get_average_brightness(FPixel* image, int imagesize);
FPixel* apply_contrast_filtering(FPixel* image, int imagesize, int average_brightness, double alpha);


#endif
