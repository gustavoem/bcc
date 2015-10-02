#ifndef POLYGON_H_
#define POLYGON_H_

#include "global.h"

class Polygon
{

private:

    // Stores the first point that defined the polygon
    //
    pair <unsigned int, unsigned int> first_point;


    // Stores the last point seen in this polygon
    //
    pair <unsigned int, unsigned int> last_point_added;

    // Storest the scan_line of the polygon
    //
    vector<vector<Edge> > scan_lines;


    void computeEdge (unsigned int, unsigned int, unsigned int, unsigned int);

public:

    // Default constructor. Receives the first point as an argument
    //
    Polygon (pair<unsigned int, unsigned int>);


    // Default destructor
    //
    virtual ~Polygon ();


    // Receives a new point
    //
    void newPoint (unsigned int, unsigned int);


    // Closes the polygon
    //
    void closePolygon (unsigned int, unsigned int);


    // Returns the scan list of the polygon
    //
    vector<vector<Edge> > getScanLines ();   


};

#endif