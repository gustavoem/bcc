#include "Polygon.h"

Polygon::Polygon (Point first_point, color c)
{
    scan_lines = vector<vector<Edge> >(ImageH + 1);
    this->first_point = first_point;
    last_point_added = first_point;
    this->c = c;
    vertices.push_back (first_point);
}


Polygon::~Polygon ()
{
    return;
}


void Polygon::computeEdge (Point p1, Point p2)
{
    //cout << "\nComputing edge: " << x1 << ","<< y1<<" ; "<<x2<<","<<y2<<endl;
    Edge new_edge;
    unsigned int x1 = p1.x;
    unsigned int x2 = p2.x;
    unsigned int y1 = p1.y;
    unsigned int y2 = p2.y;

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
    double dy = (double) e_y - s_y;
    double dx = (double) e_x - s_x;
    double slope = dy / dx;
    new_edge.max_y = e_y;
    new_edge.current_x = (double) s_x;
    new_edge.x_increment = (double) 1 / slope;

    if (scan_lines[s_y].size () == 0)
    {
        vector<Edge> new_edges_from_sy; 
        new_edges_from_sy.push_back (new_edge);
        scan_lines[s_y] = new_edges_from_sy;
    }
    else
        scan_lines[s_y].push_back (new_edge);
}


void Polygon::newPoint (Point p)
{
    computeEdge (p, last_point_added);
    last_point_added = p;
}


void Polygon::closePolygon (Point p)
{
    computeEdge (p, first_point);
    computeEdge (p, last_point_added);
    cout << "You just specified a polygon: " << endl;
    for (unsigned int i = 0; i < scan_lines.size (); i++)
        for (unsigned int j = 0; j < scan_lines[i].size (); j++)
        {
            cout << "y = " << i << " current_x = " << scan_lines[i][j].current_x << 
            " max_y = " << scan_lines[i][j].max_y << endl;
        }
}


vector<vector<Edge> > Polygon::getScanLines ()
{
    return scan_lines;
}


vector<Edge> Polygon::getScanLine (unsigned int i)
{
    vector<Edge> answ;
    if (i >= scan_lines.size ())
        cout << "Index of getScanLine is out of bounds" << endl;
    else
        answ = scan_lines[i];
    return answ;
}


color Polygon::getColor ()
{
    return c;
}