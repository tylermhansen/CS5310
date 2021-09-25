// /*
//     Tyler M. Hansen
//     Fall 2021
//     CS5310 - Graphics @ Roux Institute
//     Fractals Generation
// */

#ifndef FRACTALS_H

#define FRACTALS_H

#include <stdio.h>
#include <math.h>
#include "Image.h"

#define MAX_ITERS 255
#define MODSQ(X,Y) (X*X+Y*Y)

#define TX(X0,RAD,J,IMG) (X0 - RAD * (1.0 - 2.0 * J / IMG->cols))
#define TY(Y0,RAD,I,IMG) (Y0 + RAD * (IMG->rows - 2.0 * I) / IMG->cols)

inline int get_julia_iters(float zx, float zy, float cx, float cy) {
  int n; 
  float t_zx;
  float t_zy;
  for (n = 0; n < MAX_ITERS; n++) {
    t_zx = zx*zx - zy*zy + cx; t_zy = 2*zx*zy + cy;
    if(MODSQ(t_zx,t_zy) > 4) { break; }
    zx=t_zx; zy = t_zy; 
  }
  return n;
}

int noise2(int x, int y);

double lin_interpolation(double x, double y, double s);

double smooth_interpolation(double x, double y, double s);

double noise2d(double x, double y);

double perlin2d(double x, double y, double freq, int depth);

void perlin_image(Image *dst, double freq, int depth);

void mandelbrot(Image *dst, float x0, float y0, float rad);

void julia(Image *dst, float cx, float cy, float x0, float y0, float rad);

#endif
