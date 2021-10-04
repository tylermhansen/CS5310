/*
Polyline type for renderer in C
Author: Tyler Hansen
CS5310 @ Roux Institute Fall 2021
*/


#ifndef POLYLINE_H

#define POLYLINEH

// Include Dependencies
#include "Point.h"

// Struct Definitions
typedef struct
{
    /* 
    Polyline
    --------------------------
    The polyline structure describes a single polyline in R3. 
    */
    int zBuffer; // Whether or not to use z-buffer, should default to true 
    int numVertex; // Number of vertices
    Point *vertex; // Vertex information
} Polyline;

#endif // POLYLINE_H