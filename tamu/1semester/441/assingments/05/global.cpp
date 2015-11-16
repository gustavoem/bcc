#include "global.h"

void normalize (R3Vector * v)
{
	double v_norm = v->x * v->x + v->y * v->y + v->z * v->z;
    v_norm = sqrt (v_norm);
    v->x /= v_norm;
    v->y /= v_norm;
    v->z /= v_norm;
}