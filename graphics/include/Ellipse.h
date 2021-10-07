/*
Ellipse type for renderer in C
Author: Tyler Hansen
CS5310 @ Roux Institute Fall 2021
*/


#ifndef ELLIPSE_H

#define ELLIPSE_H

// Include Dependencies
#include "Point.h"

// Struct Definitions
typedef struct
{
    /* 
    Ellipse
    --------------------------
    The ellipse structure describes an ellipse in R3. 
    */
    double ra, rb; // Radii
    Point c; // Center 
    double a; // Angle of major axis relative to X axis
} Ellipse;

#endif // ELLIPSE_H