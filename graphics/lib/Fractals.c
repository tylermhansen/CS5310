/*
    Tyler M. Hansen
    Fall 2021
    CS5310 - Graphics @ Roux Institute
    Fractals Generation
*/

#include <stdio.h>
#include "Fractals.h"

// Draw the Mandelbrot set centered at (x0,y0)
void mandelbrot(Image *dst, float x0, float y0, float rad) {
  float x, y;
  int n;
  for(int i = 0; i < dst->rows; i++) {
    for(int j = 0; j < dst->cols; j++) {
      x = TX(x0,rad,j,dst);
      y = TY(y0,rad,i,dst);
      n = get_julia_iters(0, 0, x, y);
      image_setc(dst, i, j, 0, n / 255.0);
      image_setc(dst, i, j, 1, n / 255.0); 
      image_setc(dst, i, j, 2, n / 255.0);
    }
  }
}

// Draw the Julia set
void julia(Image *dst, float cx, float cy, float x0, float y0, float rad){
  float x, y;
  int n;
  for(int i = 0; i < dst->rows; i++) {
    for(int j = 0; j < dst->cols; j++) {
      x = TX(x0,rad,j,dst);
      y = TY(y0,rad,i,dst);
      n = get_julia_iters(x, y, cx, cy);
      image_setc(dst, i, j, 0, n / 255.0);
      image_setc(dst, i, j, 1, n / 255.0); 
      image_setc(dst, i, j, 2, n / 255.0);
    }
  }
}