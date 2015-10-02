#ifndef POLYGON_H_
#define POLYGON_H_

#include "global.h"

class Polygon
{

private:

    // Stores the first point that defined the polygon
    //
    Point first_point;


    // Stores the last point seen in this polygon
    //
    Point last_point_added;

    // Storest the scan_line of the polygon
    //
    vector<vector<Edge> > scan_lines;


    // Computes an edge updating the scan_lines vector
    //
    void computeEdge (Point, Point);


    // Polynom color
    //
    color c;


    //
    //
    vector<Point> vertices;


public:

    // Default constructor. Receives the first point as an argument
    //
    Polygon (Point, color);


    // Default destructor
    //
    virtual ~Polygon ();


    // Receives a new point
    //
    void newPoint (Point);


    // Closes the polygon
    //
    void closePolygon (Point);


    // Returns the scan list of the polygon
    //
    vector<vector<Edge> > getScanLines ();   


    // Returns the list of edges scanned in a line
    //
    vector<Edge> getScanLine (unsigned int);


    color getColor ();
};

#endif