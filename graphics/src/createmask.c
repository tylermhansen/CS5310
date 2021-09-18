/*
  This is an example of reading and writing an image using the ppmIO.c
  routines.  To manipulate the image, change the pixel color values.

  Bruce A. Maxwell updated 2021-09-05
*/

#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"

#define USECPP 0

int main(int argc, char *argv[]) {
  Pixel *image;
  int rows, cols, colors;
  long imagesize;

  if(argc < 3) {
    printf("Usage: ppmtest <input file> <output file>\n");
    exit(-1);
  }

  /* read in the image */
  image = readPPM(&rows, &cols, &colors, argv[1]);
  if(!image) {
    fprintf(stderr, "Unable to read %s\n", argv[1]);
    exit(-1);
  }

  /* calculate the image size */
  imagesize = (long)rows * (long)cols;

  /* Identify the green screen, set pixels that are part of it to 0 and those that aren't to 255.  */
  for(long i = 0; i < imagesize; i++) {
    int isInRangeOfGreenScreen = (0 <= image[i].r && image[i].r <= 100) && (80 <= image[i].g && image[i].g <= 255) && (0 <= image[i].b && image[i].b <= 120);
    image[i].r = isInRangeOfGreenScreen ? 0 : 255;
    image[i].g = isInRangeOfGreenScreen ? 0 : 255;
    image[i].b = isInRangeOfGreenScreen ? 0 : 255;
  }

  /* write out the resulting image */
  writePPM(image, rows, cols, colors /* s/b 255 */, argv[2]);

  /* free the image memory */
#if USECPP
  delete[] image;
#else
  free(image);
#endif

  return(0);
}
