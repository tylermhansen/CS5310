/*
Line type for renderer in C
Author: Tyler Hansen
CS5310 @ Roux Institute Fall 2021
*/


#ifndef LINE_H

#define LINEH

// Include Dependencies
#include "Point.h"

// Struct Definitions
typedef struct
{
    /* 
    Line
    --------------------------
    The line structure describes a single line in R3. 
    */
    int zBuffer; // Whether or not to use z-buffer, should default to true
    Point a; // Starting point
    Point b; // End point
} Line;

#endif // LINE_H