/*
  Author: Tyler Hansen
  CS5310 Graphcis @ Roux Institute, Fall 2021
  ----
  lab.c: A simple program that can be used to manipulate the contrast of a ppm image from the command line.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ppmIO.h"

#define USECPP 0


int get_average_brightness(Pixel* image, int imagesize){
  /* 
    get_average_brightness

    Returns the average brightness of all pixels in an image.
    ----------------------------------------
    parameters:
    - Pixel* image -> The image to get the average brightness for represented as an array of Pixels.
    - int imagesize -> The size of the image to get the average brightness for.

    returns:
    - int average_brightness -> The average brightness (in the range [0,255]) of all pixels in the image.
  */

  int sum_brightness = 0;
  int average_brightness = 0;

  for(int i = 0;i < imagesize; i++) {

    sum_brightness += trunc(((int)image[i].r + (int)image[i].g + (int)image[i].b) / 3);
   
  }

  average_brightness = trunc(sum_brightness / imagesize);

  return average_brightness;
}

Pixel* apply_contrast_filtering(Pixel* image, int imagesize, int average_brightness, double alpha){
  /* 
    apply_contrast_filtering

    Applies a contrast filter to a given image, either increasing or decreasing it depending on alpha.
    ----------------------------------------
    parameters:
    - Pixel* image -> The image we wish to change the contrast of represented as an array of Pixels.
    - int imagesize -> The size of the image to change the contrast of.
    - int average_brightness -> The average brightness of all pixels in the image to change the contrast of.
    - double alpha -> A scaling factor that determines how the contrast changes in the formula.

    returns:
    - Pixel* new_image -> The newly manipulated image with updated contrast.
  */
Pixel* new_image = image;
  for(int i = 0;i < imagesize; i++) {
    new_image[i].r = trunc(alpha * (new_image[i].r - average_brightness) + average_brightness);
    new_image[i].g = trunc(alpha * (new_image[i].g - average_brightness) + average_brightness);
    new_image[i].b = trunc(alpha * (new_image[i].b - average_brightness) + average_brightness);
  }
  return new_image;
}

int main(int argc, char *argv[]) {
  Pixel *image;
  int rows, cols, colors;
  long imagesize;

  if(argc < 4) {
    printf("Usage: ppmtest <input file> <output file> <contrast multiplier>\n");
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

  /* 
    From the following: https://towardsdatascience.com/image-processing-and-pixel-manipulation-photo-filters-5d37a2f992fa

    Contrast
    ----------
    The contrast ratio of an image C is defined as follows:
    (b_max - b_min) / (b_max + b_min)
    where b_max is the brightness of the brightest pixel and b_min is the brightness of the darkest pixel.
    Thus, a value of 0 is achieved when all pixels are the same brightness and 1 means that there is a maximum difference
    of 255. 

    There is a formula for how to change the contrast of each pixel in an image:
    u' = alpha(u - u*) + u*
    where u is the original brightness of that pixel, u* is the average brightness across the entire image, and alpha is a scaling factor.
    alpha = 1, no change
    alpha < 1, decrease contrast
    alpha > 1, increase contrast
  */

  // Capture user's chosen alpha.
  char *end_ptr;
  double selected_alpha = strtod(argv[3], &end_ptr);

  // Get average brightness and apply contrast filtering.
  int img_avg_brightness = get_average_brightness(image, imagesize);
  Pixel* new_img = apply_contrast_filtering(image, imagesize, img_avg_brightness, selected_alpha);

  /* write out the resulting image */
  writePPM(new_img, rows, cols, colors /* s/b 255 */, argv[2]);

  /* free the image memory */
#if USECPP
  delete[] image;
#else
  free(image);
#endif

  return(0);
}
