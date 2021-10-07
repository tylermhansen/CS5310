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
#include "Line.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Polyline.h"

// Inline Methods

// Point
extern inline void point_set2D(Point *p, double x, double y){ p->val[0] = x; p->val[1] = y; p->val[2] = 0.0; p->val[3] = 1.0; }
extern inline void point_set3D(Point *p, double x, double y, double z){ p->val[0] = x; p->val[1] = y; p->val[2] = z; p->val[3] = 1.0; }
extern inline void point_set(Point *p, double x, double y, double z, double h){ p->val[0] = x; p->val[1] = y; p->val[2] = z; p->val[3] = h; }
extern inline void point_normalize(Point *p) {p->val[0] /= p->val[3]; p->val[1] /= p->val[3]; }
extern inline void point_copy(Point *to, Point *from){ to->val[0] = from->val[0]; to->val[1] = from->val[1]; to->val[2] = from->val[2]; to->val[3] = from->val[3]; }
extern inline void point_draw(Point *p, Image *src, Color c){ image_setColor(src, p->val[1], p->val[0], c); }
extern inline void point_drawf(Point *p, Image *src, FPixel c){ image_setf(src, p->val[1], p->val[0], c); }
extern inline void point_print(Point *p, FILE *fp){ for (int i = 0; i < sizeof p->val / sizeof p->val[0]; i++){ fprintf(fp, "%.3f", p->val[i]); } }

// Line
extern inline void line_set2D(Line *l, double x0, double y0, double x1, double y1){ l->a.val[0] = x0; l->a.val[1] = y0; l->b.val[0] = x1; l->b.val[1]  = y1; }
extern inline void line_set(Line *l, Point ta, Point tb){ l->a.val[0] = ta.val[0]; l->a.val[1] = ta.val[1]; l->b.val[0] = tb.val[0]; l->b.val[1] = tb.val[1]; }
extern inline void line_zBuffer(Line *l, int flag){ l->zBuffer = flag; }
extern inline void line_normalize(Line *l){ l->a.val[0] = l->a.val[0] / l->a.val[3]; l->b.val[0] = l->b.val[0] / l->b.val[3]; l->a.val[1] = l->a.val[1] / l->a.val[3]; l->b.val[1] = l->b.val[1] / l->b.val[3]; }
extern inline void line_copy(Line *to, Line *from){ to->a = from->a; to->b = from->b; to->zBuffer = from->zBuffer; }

inline void first_fourth(Image* src, Color c, int x0, int y0, int x1, int y1)
{
    int x = x0, y = y0, dx = x1 - x0, dy = y1 - y0, ys = 1; 

    // First-Fourth Swap
    if(dy < 0) 
    {
        ys = -1; dy = -dy; 
    } 

    int e = 3 * dy - 2 * dx; 
    for(int i = 0; i < dx; i++)
    {
        image_setColor(src, y, x, c);
        while(e > 0)
        {
            y += ys; 
            e -= 2 * dx;
        }
        x++;
        e += 2 * dy;
    }
}

inline void second_third(Image* src, Color c, int x0, int y0, int x1, int y1)
{
    int x = x0, y = y0, dx = x1 - x0, dy = y1 - y0, xs = 1; 

    // Second-Third Swap
    if(dx < 0) 
    {
        xs = -1; dx = -dx; 
    } 

    int e = 3 * dx - 2 * dy; 
    for(int i = 0; i < dy; i++)
    {
        image_setColor(src, y, x, c);
        while(e > 0)
        {
            x += xs; 
            e -= 2 * dy;
        }
        y++;
        e += 2 * dx;
    }
}

inline void horizontal(Image* src, Color c, int x0, int y, int x1)
{
    for(int i = 0; i < x1 - x0; i++)
    {
        image_setColor(src, y, x0 + i, c);
    }
}

inline void vertical(Image* src, Color c, int x, int y0, int y1)
{
    for(int i = 0; i < y1 - y0; i++)
    {
        image_setColor(src, y0 + i + 1, x, c);
    }
}

extern inline void line_draw(Line *l, Image *src, Color c)
{
  int x0 = l->a.val[0], y0 = l->a.val[1], x1 = l->b.val[0], y1 = l->b.val[1]; 
  if(abs(y1 - y0) < abs(x1 - x0)) {
    if(x0 > x1)
    {
      if(y0 == y1) // Line is horizontal
      { 
        horizontal(src,c,x1,y0+1,x0);
      } 
      else 
      { 
        first_fourth(src,c,x1,y1,x0,y0); 
      }
    } 
    else 
    {
      if(y0 == y1) // Line is horizontal
      { 
        horizontal(src,c,x0,y0,x1);
      } 
      else
      { 
        first_fourth(src,c,x0,y0,x1,y1); 
      }
    }
  } 
  else
  {
    if(y0 > y1) 
    {
      if(x0 == x1) // Line is vertical
      {
        vertical(src,c,x0-1,y1,y0); 
      } 
      else 
      {
        second_third(src,c,x1,y1,x0,y0);
      }
    } 
    else
    {
      if(x0 == x1) // Line is vertical
      {
        vertical(src,c,x0,y0,y1);
      } 
      else
      {
        second_third(src,c,x0,y0,x1,y1); 
      }
    }
  }
}
extern inline void line_draw3D(Line *l, Image *src, Color c)
{
    // Draws from lower left corner
    int dx = trunc(l->a.val[0] - l->b.val[0]), dy= trunc(l->a.val[1] - l->b.val[1]), dz = trunc(l->a.val[2] - l->b.val[2]);

    int p1, p2;

    int x1 = trunc(l->b.val[0]), y1 = trunc(l->b.val[1]), y2 = trunc(l->b.val[2]), x2 = trunc(l->a.val[0]), z1 = trunc(l->a.val[1]), z2 = trunc(l->a.val[2]);

    // X axis is driving, y axis is driving, z axis is driving 
    int xs, ys, zs;

    if (x2 > x1)
    {
        xs = 1;
    }
    else
    {
        xs = -1;
    }

    if (y2 > y1)
    {
        ys = 1;
    }
    else
    {
        ys = -1;
    }
    if (z2 > z1)
    {
        zs = 1;
    }
    else{
        zs = -1;
    }

    if (dx >= dy && dx >= dz)
    {   
        p1 = 3 * dy - 2 * dx;
        p2 = 3 * dz - 2 * dx;
        while (x1 != x2)
        {
            x1 += xs;
            if (p1 >= 0){
                y1 += ys;
                p1 -= 2 * dx;
            }

            if (p2 >= 0){
                z1 += zs;
                p2 -= 2 * dx;
            }

            p1 += 2 * dy;
            p2 += 2 * dz;
            image_setz(src, x1, y1, z1);
            image_setColor(src, x1, y1, c);
        }
    }
    else if (dy >= dx && dy >= dz){ 
        p1 = 3 * dx - 2 * dy;
        p2 = 3 * dz - 2 * dy;
        while (y1 != y2)
        {
            y1 += ys;
            if (p1 >= 0)
            {
                x1 += xs;
                p1 -= 2 * dy;
            }

            if (p2 >= 0){
                z1 += zs;
                p2 -= 2 * dy;
            }

            p1 += 2 * dx;
            p2 += 2 * dz;
            image_setz(src, x1, y1, z1);
            image_setColor(src, x1, y1, c);
        }
    }
    else {        
        p1 = 3 * dy - 2 * dz;
        p2 = 3 * dx - 2 * dz;
        while (z1 != z2)
        {
            z1 += zs;
            if (p1 >= 0)
            {
                y1 += ys;
                p1 -= 2 * dz;
            }
            if (p2 >= 0)
            {
                x1 += xs;
                p2 -= 2 * dz;
            }
            p1 += 2 * dy;
            p2 += 2 * dx;
            image_setz(src, x1, y1, z1);
            image_setColor(src, x1, y1, c);
        }
    }
}

// Circle
extern inline void circle_set(Circle *c, Point tc, double tr){ c->c.val[0] = tc.val[0]; c->c.val[1] = tc.val[1]; c->r = tr; }
extern inline void circle_place_pixels_bresenham(Image *src, int x, int y, Circle* c, Color p)
{
    int xc = trunc(c->c.val[0]);
    int yc = trunc(c->c.val[1]);
    image_setColor(src, xc+x, yc+y, p);
    image_setColor(src, xc-x, yc+y, p);
    image_setColor(src, xc+x, yc-y, p);
    image_setColor(src, xc-x, yc-y, p);
    image_setColor(src, xc+y, yc+x, p);
    image_setColor(src, xc-y, yc+x, p);
    image_setColor(src, xc+y, yc-x, p);
    image_setColor(src, xc-y, yc-x, p);
}
 
extern inline void circle_draw_bresenham(Circle *c, Image *src, Color p)
{ 
    int x = 0, y = c->r; 
    int d = 3 - 2 * c->r;
    circle_place_pixels_bresenham(src, x, y, c, p);
    while (y >= x)
    {         
        x += 1;
        if (d > 0)
        {
            y -= 1;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        circle_place_pixels_bresenham(src, x, y, c, p);
    }
    
}

extern inline void circle_place_pixels_midpoint(Image *src, int x, int y, Circle* c, Color p)
{
    int xc = trunc(c->c.val[0]);
    int yc = trunc(c->c.val[1]);
    
    image_setColor(src, x + xc, y + yc, p);
    image_setColor(src, -x + xc, y + yc, p);
    image_setColor(src, x + xc, -y + yc, p);
    image_setColor(src, -x + xc, -y + yc, p);
        
    // If the generated point is on the line x = y then perimter points have already been printed
    if (x != y)
    {
        image_setColor(src, y + xc, x + yc, p);
        image_setColor(src, -y + xc, x + yc, p);
        image_setColor(src, y + xc, -x + yc, p);
        image_setColor(src, -y + xc, -x + yc, p);
    }
}

extern inline void circle_draw(Circle *c, Image *src, Color p)
{
    int x = c->r, y = 0;

    // Initialising the value of P
    int P = 1 - c->r;

    while (x > y)
    {
        y++;
         
        // Mid-point is inside or on the perimeter
        if (P <= 0)
            P = P + 2 * y + 1;
             
        // Mid-point is outside the perimeter
        else
        {
            x--;
            P = P + 2*y - 2*x + 1;
        }
         
        // All the perimeter points have already been printed
        if (x < y)
            break;
        
        circle_place_pixels_midpoint(src, x, y, c, p);
    }
}

extern inline void circle_drawFill(Circle *c, Image *src, Color p)
{

}


#endif // PRIMITIVES_H