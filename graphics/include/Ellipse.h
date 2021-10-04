/*
Ellipse type for renderer in C
Author: Tyler Hansen
CS5310 @ Roux Institute Fall 2021
*/


#ifndef ELLIPSE_H

#define ELLIPSEH

// Include Dependencies
#include "Point.h"

// Struct Definitions
typedef struct
{
    /* 
    Circle
    --------------------------
    The circle structure describes a single circle in R3. 
    */
    double r; // Radius
    Point c; // Center point
} Circle;

#endif // ELLIPSE_H