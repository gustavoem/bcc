/*
    Author: Gustavo Estrela de Matos
    Date: 11/18/15
*/

#include "global.h"

void normalize (R3Vector * v)
{
	double v_norm = norm (*v);
    v->x /= v_norm;
    v->y /= v_norm;
    v->z /= v_norm;
}


double norm (R3Vector v)
{
	double v_norm = v.x * v.x + v.y * v.y + v.z * v.z;
    v_norm = sqrt (v_norm);
    return v_norm;
}

double prod (R3Vector a, R3Vector b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}