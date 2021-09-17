#ifndef PPMIO_H

#define PPMIO_H

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} Pixel;

int get_average_brightness(Pixel* image, int imagesize);
Pixel* apply_contrast_filtering(Pixel* image, int imagesize, int average_brightness, double alpha);


Pixel *readPPM(int *rows, int *cols, int * colors, char *filename);
void writePPM(Pixel *image, int rows, int cols, int colors, char *filename);

unsigned char *readPGM(int *rows, int *cols, int *intensities, char *filename);
void writePGM(unsigned char *image, long rows, long cols, int intensities, char *filename);


#endif