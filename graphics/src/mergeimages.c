/*
  This is an example of reading and writing an image using the ppmIO.c
  routines.  To manipulate the image, change the pixel color values.

  Bruce A. Maxwell updated 2021-09-05
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Image.h"

#define USECPP 0

int main(int argc, char *argv[]) {

  if(argc < 7) {
    printf("Usage: ppmtest <foreground image> <alpha mask of foreground image> <background image> <output image> <dx> <dy>\n");
    exit(-1);
  }

  Image* foreground = image_read(argv[1]);
  Image* alpha_mask = image_read(argv[2]);
  Image* background = image_read(argv[3]);

  char* output_filename = argv[4];

  int dx = atoi(argv[5]);
  int dy = atoi(argv[6]);

  Image* result = image_create(background->rows, background->cols);

  for (int r = 0; r < background->rows; r++)
  {
    for(int c = 0; c < background->cols; c++)
    {
      if((r >= dy) && r < (foreground->rows + dy) && (c >= dx) && (c < (foreground->cols) + dx))
      {
        // If the pixel to be drawn is in the range of the mask + foreground
        image_setc(
          // Set R
          result, r, c, 0,
          (
            (image_getc(alpha_mask, r-dy, c-dx, 0)/255.0) * image_getc(foreground, r-dy, c-dx, 0) + (1 - (image_getc(alpha_mask, r-dy, c-dx, 0))/255.0) * image_getc(background, r, c, 0)
          )
        );
        image_setc(
          // Set G
          result, r, c, 1,
          (
            (image_getc(alpha_mask, r-dy, c-dx, 1)/255.0) * image_getc(foreground, r-dy, c-dx, 1) + (1 - (image_getc(alpha_mask, r-dy, c-dx, 1))/255.0) * image_getc(background, r, c, 1)
          )
        );
        image_setc(
          // Set B
          result, r, c, 2,
          (
            (image_getc(alpha_mask, r-dy, c-dx, 2)/255.0) * image_getc(foreground, r-dy, c-dx, 2) + (1 - (image_getc(alpha_mask, r-dy, c-dx, 2))/255.0) * image_getc(background, r, c, 2)
          )
        );
      }
      else{
        image_setf(result, r, c, image_getf(background, r, c));
      }
    }
  }

  image_write(result, output_filename);

  /* free the image memory */
#if USECPP
  delete[] image;
#else
  free(foreground);
  free(background);
  free(alpha_mask);
  free(result);
#endif

  return(0);
}
