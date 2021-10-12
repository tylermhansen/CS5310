/*
    Tyler M. Hansen
    Fall 2021
    CS5310 - Graphics @ Roux Institute
    Graphics Primitives
*/

#ifndef PRIMITIVES_H

#define PRIMITIVES_H

// Include Dependencies
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Image.h"

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

// Methods

// Point
// Inline Helpers
inline void point_set2D(Point *p, double x, double y){ p->val[0] = x; p->val[1] = y; p->val[2] = 0.0; p->val[3] = 1.0; }

inline void point_set3D(Point *p, double x, double y, double z){ p->val[0] = x; p->val[1] = y; p->val[2] = z; p->val[3] = 1.0; }

inline void point_set(Point *p, double x, double y, double z, double h){ p->val[0] = x; p->val[1] = y; p->val[2] = z; p->val[3] = h; }

inline void point_normalize(Point *p) {p->val[0] /= p->val[3]; p->val[1] /= p->val[3]; }

inline void point_copy(Point *to, Point *from){ to->val[0] = from->val[0]; to->val[1] = from->val[1]; to->val[2] = from->val[2]; to->val[3] = from->val[3]; }

inline void point_draw(Point *p, Image *src, Color c){ image_setColor(src, p->val[1], p->val[0], c); }

inline void point_drawf(Point *p, Image *src, FPixel c){ image_setf(src, p->val[1], p->val[0], c); }

inline void point_print(Point *p, FILE *fp){ for (int i = 0; i < sizeof p->val / sizeof p->val[0]; i++){ fprintf(fp, "%.3f", p->val[i]); } }

// Line
// Inline Helpers
inline void line_set2D(Line *l, double x0, double y0, double x1, double y1){ l->a.val[0] = x0; l->a.val[1] = y0; l->b.val[0] = x1; l->b.val[1]  = y1; }

inline void line_set(Line *l, Point ta, Point tb){ l->a.val[0] = ta.val[0]; l->a.val[1] = ta.val[1]; l->b.val[0] = tb.val[0]; l->b.val[1] = tb.val[1]; }

inline void line_zBuffer(Line *l, int flag){ l->zBuffer = flag; }

inline void line_normalize(Line *l){ l->a.val[0] = l->a.val[0] / l->a.val[3]; l->b.val[0] = l->b.val[0] / l->b.val[3]; l->a.val[1] = l->a.val[1] / l->a.val[3]; l->b.val[1] = l->b.val[1] / l->b.val[3]; }

inline void line_copy(Line *to, Line *from){ to->a = from->a; to->b = from->b; to->zBuffer = from->zBuffer; }

// Non-Inline Helpers
void first_fourth(Image* src, Color c, int x0, int y0, int x1, int y1);

void second_third(Image* src, Color c, int x0, int y0, int x1, int y1);

void horizontal(Image* src, Color c, int x0, int y, int x1);

void vertical(Image* src, Color c, int x, int y0, int y1);

void line_draw(Line *l, Image *src, Color c);

void line_draw3D(Line *l, Image *src, Color c);

// Circle
inline void circle_set(Circle *c, Point tc, double tr){ c->c.val[0] = tc.val[0]; c->c.val[1] = tc.val[1]; c->r = tr; }

void circle_place_pixels_bresenham(Image *src, int x, int y, Circle* c, Color p);

void circle_draw_bresenham(Circle *c, Image *src, Color p);

void circle_place_pixels_midpoint(Image *src, int x, int y, Circle* c, Color p);

void circle_draw(Circle *c, Image *src, Color p);

void circle_drawFill(Circle *c, Image *src, Color p);

// Ellipse

// Polyine
// Constructors & Destructors:
Polyline *polyline_create(void);

Polyline *polyline_createp(int numV, Point *vlist);

void polyline_free(Polyline *p);

void polyline_init(Polyline *p);

// Utility:
void polyline_set(Polyline *p, int numV, Point *vlist);

void polyline_clear(Polyline *p);

void polyline_draw(Polyline *p, Image *src, Color c);

// Inline Helpers:

inline void polyline_zBuffer(Polyline *p, int flag){ p->zBuffer = flag; }

inline void polyline_copy(Polyline *to, Polyline *from){ polyline_set(to, from->numVertex, from->vertex); }


#endif // PRIMITIVES_H