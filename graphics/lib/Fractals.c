/*
    Tyler M. Hansen
    Fall 2021
    CS5310 - Graphics @ Roux Institute
    Fractals Generation
*/

#include <stdio.h>
#include "Fractals.h"

static const int PERLIN_SEED = 0;

static const unsigned char HASH[] = // 0-255 inclusive in random order, generated from numbergenerator.org by Tyler Hansen 09/25
{
  202,149,196,208,117,12,110,162,119,224,53,201,146,
  132,63,252,242,93,216,72,213,200,230,10,204,104,47,
  203,97,241,126,129,9,24,50,134,28,175,38,238,186,49,
  106,27,191,0,26,108,112,3,59,130,66,164,86,17,120,143,
  184,151,254,115,144,214,192,82,55,141,206,45,173,235,
  233,166,247,227,239,178,77,122,31,190,170,89,83,167,
  225,198,180,137,163,193,11,116,153,76,88,176,183,217,
  195,138,67,236,209,37,36,123,16,142,52,6,34,94,30,181,
  64,1,250,177,152,220,194,58,226,231,109,33,171,54,18,
  127,154,158,40,207,39,68,155,5,42,205,135,101,219,107,
  92,74,128,35,248,14,121,96,78,43,172,81,174,99,234,113,
  124,118,60,95,62,7,156,100,187,169,157,237,215,84,253,
  102,160,57,46,140,211,48,21,245,249,228,69,251,133,75,
  179,25,103,255,168,44,221,19,218,22,73,244,165,71,243,
  223,161,150,111,136,105,8,182,85,41,90,229,139,131,23,
  199,79,29,15,51,240,210,125,32,2,4,13,222,148,212,114,
  188,91,147,185,56,197,87,232,70,98,145,80,20,189,246,159,61,65
};

// Hash function that returns a unique value based on the table above and the seed value for x and y.
int noise2(int x, int y)
{
  int y_idx = (y + PERLIN_SEED) % 256;
  if (y_idx < 0)
    y_idx += 256;
  int x_idx = (HASH[y_idx] + x) % 256;
  if (x_idx < 0)
    x_idx += 256;
  int res = HASH[x_idx];
  return res;
}

// Linear interpolation
double lin_interpolation(double x, double y, double s)
{
  return x + s * (y - x);
}

// Smoother interpolation
double smooth_interpolation(double x, double y, double s)
{
  return lin_interpolation(x, y, s * s * (3 - 2 * s));
}

// Interpolated noise based on four points surrounding target 2D point
double noise2d(double x, double y)
{
  int x_int = floor(x);
  int y_int = floor(y);

  double x_frac = x - x_int;
  double y_frac = y - y_int;

  int a = noise2(x_int, y_int);
  int b = noise2(x_int + 1, y_int);
  int c = noise2(x_int, y_int + 1);
  int d = noise2(x_int+ 1, y_int + 1);

  double lo = smooth_interpolation(a, b, x_frac);
  double hi = smooth_interpolation(c, d, x_frac);
  double res = smooth_interpolation(lo, hi, y_frac);
  
  return res;
}

// Repeatedly get noise with different amplitudes and frequencies based on depth
double perlin2d(double x, double y, double freq, int depth)
{
  double xn = x * freq;
  double yn = y * freq;
  double amp = 1.0;
  double final = 0;
  double div = 0.0;
  
  for (int i = 0; i < depth; i++)
  {
    div += 256 * amp;
    final += noise2d(xn, yn) * amp;
    amp /= 2;
    xn *= 2;
    yn *= 2;
  }
  
  return final / div;
}

void perlin_image(Image *dst, double freq, int depth)
{
  float n;
  for(int i = 0; i < dst->rows; i++)
  {
    for(int j = 0; j < dst->cols; j++)
    {
      n = perlin2d(i, j, freq, depth);
      image_setc(dst, i, j, 0, n);
      image_setc(dst, i, j, 1, n); 
      image_setc(dst, i, j, 2, n);
    }
  }
}

// Draw the Mandelbrot set centered at (x0, y0)
void mandelbrot(Image *dst, float x0, float y0, float rad) {
  float x, y;
  int n;
  for(int i = 0; i < dst->rows; i++)
  {
    for(int j = 0; j < dst->cols; j++)
    {
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
  for(int i = 0; i < dst->rows; i++)
  {
    for(int j = 0; j < dst->cols; j++)
    {
      x = TX(x0,rad,j,dst);
      y = TY(y0,rad,i,dst);
      n = get_julia_iters(x, y, cx, cy);
      image_setc(dst, i, j, 0, n / 255.0);
      image_setc(dst, i, j, 1, n / 255.0); 
      image_setc(dst, i, j, 2, n / 255.0);
    }
  }
}