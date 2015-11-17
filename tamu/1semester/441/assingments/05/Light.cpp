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


Color Light::getDiffuseLight (R3Vector N, R3Vector p0, double k_d)
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
    double LN_kd = LN * k_d;
    diffuselight.r = intensity.r * LN_kd;
    diffuselight.g = intensity.g * LN_kd;
    diffuselight.b = intensity.b * LN_kd;
    return diffuselight;
}


Color Light::getSpecularLight (R3Vector N, R3Vector p0, R3Vector E, double k_s, double n)
{
    R3Vector L;
    L.x = center.x - p0.x;
    L.y = center.y - p0.y;
    L.z = center.z - p0.z;
    normalize (&L);

    double LN = N.x * L.x + N.y * L.y + N.z * L.z;
    if (LN < 0)
        LN = 0;

    R3Vector R;
    R.x = 2 * LN * N.x - L.x;
    R.y = 2 * LN * N.y - L.y;
    R.z = 2 * LN * N.z - L.z;

    double ER = E.x * R.x + E.y * R.y + E.z * R.z;
    double ks_ERn = pow (ER, n) * k_s;
    Color specularlight;
    specularlight.r = intensity.r * ks_ERn;
    specularlight.g = intensity.g * ks_ERn;
    specularlight.b = intensity.b * ks_ERn;
    return specularlight;
}


R3Vector Light::getCenter ()
{
    return center;
}