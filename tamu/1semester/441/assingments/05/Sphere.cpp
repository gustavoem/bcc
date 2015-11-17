#include "Sphere.h"

Sphere::Sphere (R3Vector pos, double size, Color color, Material material) : 
                Object (pos, color, material)
{
    this->size = size;
}

Sphere::~Sphere ()
{
    return;
}


// Eye is at (0, 0, 0)
// Describing a point of the ray as s*u we can get that an intersection with the sphere
// by calculation the two solutions for:
//      s^2 - 2(u.dP)s + |dP|^2 - r^2
//      where dP = P_c - P_0
Intersection * Sphere::intersect (R3Vector u, R3Vector p0)
{       
    Intersection * intersection = NULL;
    double u_dp = u.x * (center.x - p0.x)+
                  u.y * (center.y - p0.y) + 
                  u.z * (center.z - p0.z);
    double dp_mod_square = pow (center.x - p0.x, 2) +
                           pow (center.y - p0.y, 2) + 
                           pow (center.z - p0.z, 2);
    double discriminant = pow (u_dp, 2) - dp_mod_square + pow (size, 2);

    double s = -1;
    if (discriminant >= 0)
    {
        Color c;
        c.r = color.r;
        c.g = color.g;
        c.b = color.b;        
        
        double s1 = u_dp + sqrt (discriminant);
        double s2 = u_dp - sqrt (discriminant);
        double s_1st;
        double s_2nd;

        if (s1 < s2)
        {
            s_1st = s1;
            s_2nd = s2;
        }
        else
        {
            s_1st = s2;
            s_2nd = s1;
        }

        if (s_1st > 1e-5)
            s = s_1st;
        else
            if (s_2nd > 1e-5)
                s = s_2nd;
    }
    
    if (s > 1e-5)
    {
        R3Vector p = p0;
        p.x += s * u.x;
        p.y += s * u.y;
        p.z += s * u.z;
        intersection = new Intersection;
        intersection->color = color;
        intersection->point = p;
        intersection->object = this;
    }

    return intersection;
}


Material Sphere::getMaterial ()
{
    return material;
}


R3Vector Sphere::getNormal (R3Vector p)
{
    R3Vector n;
    n.x = p.x - center.x;
    n.y = p.y - center.y;
    n.z = p.z - center.z;

    normalize (&n);
    return n;
}