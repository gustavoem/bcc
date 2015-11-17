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
vector<Intersection> Sphere::intersect (R3Vector u, R3Vector p0)
{       
    vector<Intersection> intersections;
    double u_dp = u.x * (center.x - p0.x)+
                  u.y * (center.y - p0.y) + 
                  u.z * (center.z - p0.z);
    double dp_mod_square = pow (center.x - p0.x, 2) +
                           pow (center.y - p0.y, 2) + 
                           pow (center.z - p0.z, 2);
    double discriminant = pow (u_dp, 2) - dp_mod_square + pow (size, 2);

    if (discriminant >= 0)
    {
        Color c;
        c.r = color.r;
        c.g = color.g;
        c.b = color.b;        
        
        double s;
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

        R3Vector p1;
        R3Vector p2;
        p1.x = s_1st * u.x + p0.x;
        p1.y = s_1st * u.y + p0.y;
        p1.z = s_1st * u.z + p0.z;
        p2.x = s_2nd * u.x + p0.x;
        p2.y = s_2nd * u.y + p0.y;
        p2.z = s_2nd * u.z + p0.z;

        Intersection intersect;
        intersect.color = c;
        intersect.point = p1;
        intersect.object = this;
        if (s_1st > 0)
            intersections.push_back (intersect);

        if (s1 != s2)
        {
            intersect.point = p2;
            if (s_2nd > 0)
                intersections.push_back (intersect);
        }
    }
    return intersections;
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