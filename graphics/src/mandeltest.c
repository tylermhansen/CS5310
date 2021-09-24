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

	mandelbrot( src, 1.765, .073, 0.01);

  image_write( src, "mandelbrot.ppm");

  julia(src, -0.7, 0.27015, 0, 0, 1.75);

  image_write( src, "julia.ppm");

  image_free( src );

  return(0);
}
