#include "Sphere.h"

Sphere::Sphere (Vector pos, double size, Color color, Material material)
{
    center = pos;
    this->size = size;
    this->color = color;
    this->material = material;
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
pair<Color, Vector> * Sphere::intersect (Vector u, Vector p0)
{       
    double u_dp = u.x * (center.x - p0.x)+
                  u.y * (center.y - p0.y) + 
                  u.z * (center.z - p0.z);
    double dp_mod_square = pow (center.x - p0.x, 2) +
                           pow (center.y - p0.y, 2) + 
                           pow (center.z - p0.z, 2);
    double discriminant = pow (u_dp, 2) - dp_mod_square + pow (size, 2);

    if (discriminant < 0)
    {
        return NULL;
    }
    else
    {
        Color c;
        c.r = color.r;
        c.g = color.g;
        c.b = color.b;        
        
        double s;
        double s1 = u_dp + sqrt (discriminant);
        double s2 = u_dp - sqrt (discriminant);
        if (s1 < s2)
            s = s1;
        else
            s = s2;

        Vector p;
        p.x = s * u.x + p0.x;
        p.y = s * u.y + p0.y;
        p.z = s * u.z + p0.z;

        pair<Color, Vector> * intersect = new pair<Color, Vector> ();
        intersect->first = c;
        intersect->second = p;
        return intersect;
    }

}


Material Sphere::getMaterial ()
{
    return material;
}


Vector Sphere::getNormal (Vector p)
{
    Vector n;
    n.x = p.x - center.x;
    n.y = p.y - center.y;
    n.z = p.z - center.z;

    normalize (&n);
    return n;
}