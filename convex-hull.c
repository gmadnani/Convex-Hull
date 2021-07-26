/* * * * * * *
 * Implementation of the Inside Hull algorithm for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2019
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Insert Name Here>
 */

//                   WRITE YOUR IMPLEMENTATION HERE
//
// You should fill in the function definitions for orientation() and
// inside_hull() in this file.
//
// Don't be shy to add any extra functions or types you may need.

#include <stdio.h>
#include <stdlib.h>

#include "convex-hull.h"

// Returns the orientation of Point p2 in relation to the line segment p0p1.
// If p2 is to the left of p0p1 then it returns LEFT ('l'), if p2 is to the
// right it returns RIGHT ('r').
// If p0, p1 and p2 are collinear then COLLINEAR ('c') is returned.
/*char orientation(Point p0, Point p1, Point p2) {
  // TODO: Implement orientation()
  fprintf(stderr, "Error: orientation() not implemented\n");
  exit(EXIT_FAILURE);
}*/

char orientation(Point p0, Point p1, Point p2){
	
	double val =(p1.x - p0.x)*(p2.y - p0.y) - (p2.x - p0.x)*(p1.y - p0.y);

    if (val == 0) return 'c';  
    return (val > 0)? 'l': 'r';  
}

// Takes a polygon (i.e. an array of points) given in counter-clockwise order
// with n points.
//
// Stores the points of the convex hull into the hull array (the last point
// should NOT be the same as the first point), and returns the number of
// points which are in the convex hull.
//
// If three successive points in the polygon are collinear then the algorithm
// should terminate and COLLINEAR_POINTS should be returned.
//
// If an error occurs this function should return INSIDE_HULL_ERROR.
int inside_hull(Point *polygon, int n, Point *hull) {
  // TODO: Implement the InsideHull algorithm
  //fprintf(stderr, "Error: inside_hull() not implemented\n");
  //exit(EXIT_FAILURE);
	Point* D = (Point*)malloc(sizeof(Point)*(2*n+1));
	int bot = n-2, top = bot+3;    
    D[bot] = D[top] = polygon[2];        
    if (orientation(polygon[0], polygon[1], polygon[2]) == 'l') {
        D[bot+1] = polygon[0];
        D[bot+2] = polygon[1];           
    }

    else {
        D[bot+1] = polygon[1];
        D[bot+2] = polygon[0];           
    }

    
    for (int i=3; i < n; i++) {   
        
        if ((orientation(D[bot], D[bot+1], polygon[i]) =='l') &&
            (orientation(D[top-1], D[top], polygon[i]) =='l') )
                 continue;         
       
        while (orientation(D[bot], D[bot+1], polygon[i]) == 'r'||orientation(D[bot], D[bot+1], polygon[i]) == 'c')
            ++bot;                 
        D[--bot] = polygon[i];     

        while (orientation(D[top-1], D[top], polygon[i]) == 'r'||orientation(D[top-1], D[top], polygon[i]) == 'c')
            --top;                 
        D[++top] = polygon[i];     
    }

    int h;        
    for (h=0; h <= (top-bot); h++)
        hull[h] = D[bot + h];

    free(D);
    return h-1;
}
