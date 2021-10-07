/*
Color type for renderer in C
Author: Tyler Hansen
CS5310 @ Roux Institute Fall 2021
*/


#ifndef COLOR_H

#define COLOR_H

// Include Dependencies

// Struct Definitions
typedef struct
{
    /* 
    Color
    --------------------------
    Describes the color of a pixel in RGB color format.
    */
    float c[3];
} Color;

// Inline Methods
inline void color_copy(Color *to, Color *from){ to = from; }

inline void color_set(Color *to, float r, float g, float b){ to->c[0] = r; to->c[1] = g; to->c[2] = b; }

#endif // COLOR_H