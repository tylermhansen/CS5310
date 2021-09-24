/*
	Tyler Hansen

    Creates a Julia set at a user's specified location.
*/

#include <stdio.h>
#include <stdlib.h>
#include "Fractals.h"

int main(int argc, char *argv[]) {
    Image *src;
    float x0, y0, rad, cx, cy;
    int rows, cols;
    
    if(argc < 9) {
        printf("Usage: julia <output file> <img rows> <img cols> <x0> <y0> <radius> <cx> <cy>\n");
        exit(-1);
    }

    rows = atoi(argv[2]);
    cols = atoi(argv[3]);
    x0 = atof(argv[4]);
    y0 = atof(argv[5]);
    rad = atof(argv[6]);
    cx = atof(argv[7]);
    cy  = atof(argv[8]);

    src = image_create(rows, cols);

    julia(src, cx, cy, x0, y0, rad);

    image_write(src, argv[1]);

    image_free(src);

  return(0);
}
