#include "Light.h"

Light::Light (R3Vector pos, Color color)
{
    center = pos;
    intensity = color;
}


Light::~Light ()
{
    return;
}


Color Light::getIntensity ()
{
	return intensity;
}


Color Light::getDiffuseLight (R3Vector N, R3Vector p0)
{
	R3Vector L;
	L.x = center.x - p0.x;
	L.y = center.y - p0.y;
	L.z = center.z - p0.z;
	normalize (&L);

	double LN = N.x * L.x + N.y * L.y + N.z * L.z;
	if (LN < 0)
		LN = 0;

	Color diffuselight;
	diffuselight.r = intensity.r * LN;
	diffuselight.g = intensity.g * LN;
	diffuselight.b = intensity.b * LN;
	return diffuselight;
}