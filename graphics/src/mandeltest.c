/*
	Bruce A. Maxwell
	Fall 2013

  Creates a Mandelbrot set at a selected location
*/
#include "Fractals.h"

int main(int argc, char *argv[]) {
  Image *src;

	src = image_create(750, 1000);

	mandelbrot( src, 0, 0, 2);

  image_write( src, "mandelbrot-full.ppm");

	mandelbrot( src, -0.4621603, -0.5823998, 0.005);

  image_write( src, "mandelbrot.ppm");

  julia(src, -0.7, 0.27015, 0, 0, 1.75);

  image_write( src, "julia.ppm");

  perlin_image(src, 0.001, 4);

  image_write(src, "smoke.ppm");

   perlin_image(src, 0.1, 4);

  image_write(src, "perlin_high_freq.ppm");

  image_free( src );

  return(0);
}
