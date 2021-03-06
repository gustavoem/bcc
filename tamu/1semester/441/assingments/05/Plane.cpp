/*
    Author: Gustavo Estrela de Matos
    Date: 11/18/15
*/
    
#include "Plane.h"

Plane::Plane (R3Vector pos, Color color, Material material, R3Vector normal) : 
                Object (pos, color, material)
{
    normalize (&normal);
    this->normal = normal;
}


Plane::~Plane ()
{
    return;
}


// Plane equation: (center - p).normal = 0
// Line equation:  p0 + su
// Intersection
//      (center - p0 + su).normal = 0
//  Lets call center - p0 = dp
//      (dp - su).normal = 0
//      s(u.normal) = dp.normal
//  Now, if u.normal != 0, i.e u is not parallel to the plan, then there is an 
//  intersection point
//      s = dp.normal / u.normal
//
// OBS: we don't draw planes aligned to the vision, with u parallel to the plan and
// with p0 inside the plan
Intersection * Plane::intersect (R3Vector u, R3Vector p0)
{
    // First, if u is perpendicular to the normal, there is no intersection
    double un = u.x * normal.x + u.y * normal.y + u.z * normal.z;

    double dpn = (center.x - p0.x) * normal.x + 
                 (center.y - p0.y) * normal.y +
                 (center.z - p0.z) * normal.z;

    // Finds the intersection point
    double s = dpn / un;
    if (s < +1e-5)
        return NULL;
    R3Vector p = p0;
    p.x += u.x * s;
    p.y += u.y * s;
    p.z += u.z * s;

    Intersection * intersect = new Intersection;
    intersect->color = color;
    intersect->point = p;
    intersect->object = this;
    return intersect;
}


Material Plane::getMaterial ()
{
    return material;
}


R3Vector Plane::getNormal (R3Vector p)
{
    return normal;
}