/*
Point type for renderer in C
Author: Tyler Hansen
CS5310 @ Roux Institute Fall 2021
*/


#ifndef POINT_H

#define POINT_H

// Include Dependencies

// Struct Definitions
typedef struct
{
    /* 
    Point
    --------------------------
    The point structure describes a single point in R3. 
    */
    double val[4];
} Point;

#endif // POINT_H