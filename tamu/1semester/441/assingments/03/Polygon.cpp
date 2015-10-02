#include "Polygon.h"

Polygon::Polygon (pair<unsigned int, unsigned int> first_point)
{
    scan_lines = vector<vector<Edge> >(ImageH + 1);
    this->first_point = first_point;
    last_point_added = first_point;
}


Polygon::~Polygon ()
{
    return;
}


void Polygon::computeEdge (unsigned int x1, unsigned int y1,
                           unsigned int x2, unsigned int y2)
{
    Edge new_edge;
    unsigned int s_y, e_y;
    unsigned int s_x, e_x;
    if (y2 > y1)
    {
        s_y = y1;
        s_x = x1;
        e_y = y2;
        e_x = x2;
    }
    else
    {
        s_y = y2;
        s_x = x2;   
        e_y = y1;
        e_x = x1;
    }
    float slope = (e_y - s_y) / (float)(e_x - s_y);
    new_edge.max_y = e_y;
    new_edge.current_x = (float) s_x;
    new_edge.x_increment = 1 / slope;
    
    if (scan_lines[s_y].size () == 0)
    {
        vector<Edge> new_edges_from_sy; 
        new_edges_from_sy.push_back (new_edge);
        scan_lines[s_y] = new_edges_from_sy;
    }
    else
        scan_lines[s_y].push_back (new_edge);
}


void Polygon::newPoint (unsigned int x, unsigned int y)
{
    computeEdge (x, y, last_point_added.first, last_point_added.second);
    last_point_added.first = x;
    last_point_added.second = y;
}


void Polygon::closePolygon (unsigned int x, unsigned int y)
{
    computeEdge (x, y, first_point.first, first_point.second);
}

vector<vector<Edge> > Polygon::getScanLines ()
{
    return scan_lines;
}