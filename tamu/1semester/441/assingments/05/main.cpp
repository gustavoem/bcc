/*
    Author: Gustavo Estrela de Matos
    Date: 11/18/15
*/

#include <GL/glut.h>

#include "Object.h"
#include "global.h"
#include "Sphere.h"
#include "Light.h" 
#include "Plane.h"

#include <vector>       
#include <fstream>

#define ImageW 800
#define ImageH 800
#define FILM_WALL_Z 1000
#define MAX_DEPTH 10000
#define MAX_REFLECTION 7

float framebuffer[ImageH][ImageW][3];

// Elements to be drawn
//
vector<Object *> objs;


// Light sources
// 
vector<Light *> lights;


// Ambient light
//
Light * ambent_light;


// Eye position
//
R3Vector eye;


int state = 0;


// Keyboard callback
void keyboard (unsigned char key, int x, int y);

// Draws the scene
void drawit (void);

// Clears framebuffer to black
void clearFramebuffer ();

// Sets pixel x,y to the color RGB
void setFramebuffer (int x, int y, float R, float G, float B);

// Draws in the buffer
void display (void);

// Initializes objects
void init (void);

// Traces the ray and determines the color of the pixel
void rayCast (int x, int y);

// Returns the intersection of the ray to the nearest object
Intersection * intersectElement (R3Vector u, R3Vector p0, bool intersectLights);

// Returns the color of a point being looked by V in the object obj
Color pointColor (Object * obj, R3Vector inter_point, R3Vector V, unsigned int level);

int main (int argc, char** argv)
{
    glutInit (&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize (ImageW,ImageH);
    glutInitWindowPosition (100,100);
    glutCreateWindow ("Gustavo Estrela - Assignment 5");
    glutDisplayFunc (display);
    glutKeyboardFunc (keyboard);
    init ();
    glutMainLoop ();
    return 0;
}


void drawit (void)
{
   glDrawPixels (ImageW,ImageH,GL_RGB,GL_FLOAT,framebuffer);
   glFlush ();
}


void clearFramebuffer ()
{
    int i, j;

    for (i = 0;i < ImageH; i++)
    {
        for (j = 0;j < ImageW; j++)
        {
            framebuffer[i][j][0] = 0.0;
            framebuffer[i][j][1] = 0.0;
            framebuffer[i][j][2] = 0.0;
        }
    }
}


void setFramebuffer (int x, int y, float R, float G, float B)
{
    if (R <= 1.0)
        if (R >= 0.0)
            framebuffer[x][y][0] = R;
        else
            framebuffer[x][y][0] = 0.0;
    else
        framebuffer[x][y][0] = 1.0;

    if (G <= 1.0)
        if (G >= 0.0)
            framebuffer[x][y][1] = G;
        else
            framebuffer[x][y][1] = 0.0;
    else
        framebuffer[x][y][1] = 1.0;

    if (B <= 1.0)
        if (B >= 0.0)
            framebuffer[x][y][2] = B;
        else
            framebuffer[x][y][2] = 0.0;
    else
        framebuffer[x][y][2] = 1.0;
}


void init (void)
{
    eye.x = 400;
    eye.y = 400;
    eye.z = 0;

    if (state == 0)
    {
        // Sphere 1
        Color color;
        color.r = 0;
        color.g = 1;
        color.b = 1;
        R3Vector center;
        center.x = 100;
        center.y = 100;
        center.z = FILM_WALL_Z + 200;
        Material material;
        material.k_a = 0.2;
        material.k_d = 0.3;
        material.k_s = 0.6;
        material.n = 100;
        material.k_r = 0.1;
        Sphere * sphere1 = new Sphere (center, 100, color, material);
        objs.push_back (sphere1);

        color.r = 1;
        color.g = 1;
        color.b = 1;
        center.y = 50;
        center.z = FILM_WALL_Z + 400;
        center.x = 400;
        material.k_a = 0.4;
        material.k_d = 0.0;
        material.k_s = 0;
        material.n = 10;
        material.k_r = 0.0;
        Sphere * sphere2 = new Sphere (center, 50, color, material);
        objs.push_back (sphere2);

        center.x = 500;
        material.k_a = 0.4;
        material.k_d = 0.5;
        material.k_s = 0.0;
        material.n = 10;
        material.k_r = 0.0;
        Sphere * sphere3 = new Sphere (center, 50, color, material);
        objs.push_back (sphere3);

        center.x = 600;
        material.k_a = 0.4;
        material.k_d = 0.5;
        material.k_s = 0.5;
        material.n = 10;
        material.k_r = 0.0;
        Sphere * sphere4 = new Sphere (center, 50, color, material);
        objs.push_back (sphere4);

        center.x = 700;
        material.k_a = 0.4;
        material.k_d = 0.5;
        material.k_s = 0.5;
        material.n = 10;
        material.k_r = 0.5;
        Sphere * sphere5 = new Sphere (center, 50, color, material);
        objs.push_back (sphere5);


        // Walls
        color.r = .7;
        color.g = .7;
        color.b = .7;
        center.x = 0;
        center.y = 0;
        center.z = FILM_WALL_Z;
        material.k_a = 0.3;
        material.k_d = 0.7;
        material.k_s = 0;
        R3Vector normal;
        normal.x = 1;
        normal.y = 0;
        normal.z = 0;
        material.n = 2;
        material.k_r = 0;
        // left plane
        Plane * plane1 = new Plane (center, color, material, normal);
        objs.push_back (plane1);
        
        // floor plane
        normal.x = 0;
        normal.y = 1;
        normal.z = 0;
        Plane * plane2 = new Plane (center, color, material, normal);
        objs.push_back (plane2);
        
        center.x = 800;
        center.y = 800;
        
        // ceiling
        normal.x = 0;
        normal.y = -1;
        normal.z = 0;
        Plane * plane3 = new Plane (center, color, material, normal);
        objs.push_back (plane3);

        // right plane
        normal.x = -1;
        normal.y = 0;
        normal.z = 0;
        Plane * plane4 = new Plane (center, color, material, normal);
        objs.push_back (plane4);

        // back plane
        material.k_r = 1;
        material.k_a = 0;
        material.k_d = 0;
        material.k_s = 0;
        center.z = FILM_WALL_Z + 1000;
        normal.x = 0;
        normal.y = 0;
        normal.z = -1;
        Plane * plane5 = new Plane (center, color, material, normal);
        objs.push_back (plane5);
        material.k_r = 0;

        // Light
        color.r = 255 / 255;
        color.g = 214.0 / 255;
        color.b = 170.0 / 255;
        center.x = 400;
        center.y = 790;
        center.z = FILM_WALL_Z + 100;
        material.k_a = 1;
        material.k_d = 0;
        material.k_s = 0;
        Light * light1 = new Light (center, color);
        lights.push_back (light1);
        objs.push_back (light1);

        color.r = 0.5;
        color.g = 70.0 / 255;
        color.b = 0;
        center.x = 400;
        center.y = 20;
        center.z = FILM_WALL_Z;
        material.k_a = 2;
        material.k_d = 0;
        material.k_s = 0;
        Light * light2 = new Light (center, color);
        lights.push_back (light2);
        objs.push_back (light2);

    }
    else
    {
        Color color;
        R3Vector center;
        center.x = 0;
        center.y = 0;
        center.z = FILM_WALL_Z;
        Material material;
        material.k_a = 0;
        material.k_d = .1;
        material.k_s = .1;
        material.k_r = .7;
        material.n = 2;
        R3Vector normal;
        
        // floor
        color.r = 0;
        color.g = 1;
        color.b = 0;
        normal.x = 0;
        normal.y =  1;
        normal.z = 0;
        Plane * plane2 = new Plane (center, color, material, normal);
        objs.push_back (plane2);

        // right plane
        center.x = 400;
        center.y = 800 * (sqrt (3) / 2);
        color.r = 0;
        color.g = 0;
        color.b = 1;
        normal.x = -sqrt (3);
        normal.y =  -1;
        normal.z = 0;
        normalize (&normal);
        Plane * plane3 = new Plane (center, color, material, normal);
        objs.push_back (plane3);
        
        // left plane
        color.r = 1;
        color.g = 0;
        color.b = 0;
        normal.x = sqrt (3);
        normal.y =  -1;
        normal.z = 0;
        normalize (&normal);
        Plane * plane1 = new Plane (center, color, material, normal);
        objs.push_back (plane1);


        // bacl plane
        color.r = .8;
        color.g = .8;
        color.b = .8;

        material.k_r = 0;
        material.k_a = 1;
        material.k_d = 0;
        material.k_s = 0;
        center.z = FILM_WALL_Z + 5000;
        normal.x = 0;
        normal.y = 0;
        normal.z = -1;
        Plane * plane5 = new Plane (center, color, material, normal);
        objs.push_back (plane5);
        material.k_r = 0;

        color.r = 1;
        color.g = 0;
        color.b = 0;
        center.x = 400;
        center.y = 800 * (sqrt (3) / 4) + 50;
        center.z = FILM_WALL_Z + 4900;
        material.k_a = 1;
        material.k_d = 0.6;
        material.k_s = 0.6;
        material.n = 3;
        material.k_r = 0;
        Sphere * sphere1 = new Sphere (center, 100, color, material);
        objs.push_back (sphere1);

        color.r = 0;
        color.g = 1;
        color.b = 0;
        center.x = 400 - 100;
        center.y = 800 * (sqrt (3) / 4) - 100;
        center.z = FILM_WALL_Z + 4900;
        material.k_a = 1;
        material.k_d = 0.6;
        material.k_s = 0.6;
        material.n = 3;
        material.k_r = 0;
        Sphere * sphere2 = new Sphere (center, 100, color, material);
        objs.push_back (sphere2);

        color.r = 0;
        color.g = 0;
        color.b = 1;
        center.x = 400 + 100;
        center.y = 800 * (sqrt (3) / 4) - 100;
        center.z = FILM_WALL_Z + 4900;
        material.k_a = 1;
        material.k_d = 0.6;
        material.k_s = 0.6;
        material.n = 3;
        material.k_r = 0;
        Sphere * sphere3 = new Sphere (center, 100, color, material);
        objs.push_back (sphere3);

        // Light
        color.r = 0.3;
        color.g = 0.3;
        color.b = 0.3;
        center.x = 400;
        center.y = 800 * (sqrt (3) / 4);
        center.z = FILM_WALL_Z - 4900;
        material.k_a = 1;
        material.k_d = 0;
        material.k_s = 0;
        Light * light1 = new Light (center, color);
        lights.push_back (light1);
        objs.push_back (light1);
    }

    Color color;
    R3Vector center;
    color.r = 1;
    color.g = 1;
    color.b = 1;
    center.x = 400;
    center.y = 0;
    center.z = 0;
    ambent_light = new Light (center, color);
    clearFramebuffer ();
}


void rayCast (int x, int y)
{
    // Ray tracing R3Vector
    R3Vector u;
    u.x = x - eye.x;
    u.y = y - eye.y;
    u.z = FILM_WALL_Z - eye.z;
    normalize (&u);
    
    Intersection * inter = intersectElement (u, eye, true);
    if (inter == NULL) return;

    Object * obj = inter->object;
    R3Vector inter_point = inter->point;
    Color c = pointColor (obj, inter_point, u, 0);
    delete inter;

    setFramebuffer (y, x, c.r, c.g, c.b);
}


Color pointColor (Object * obj, R3Vector inter_point, R3Vector V, unsigned int level)
{
    Color c = obj->getColor ();
    // Ambient light
    Material mt = obj->getMaterial ();
    double k_a = mt.k_a;
    c.r *= ambent_light->getIntensity ().r  * k_a;
    c.g *= ambent_light->getIntensity ().g  * k_a;
    c.b *= ambent_light->getIntensity ().b  * k_a;
    R3Vector N = obj->getNormal (inter_point);

    // Diffuse and Specular Light
    for (unsigned int j = 0; j < lights.size (); j++)
    {
        Light * light = lights[j];

        // Verifies if its in shadow
        R3Vector itToLight = light->getCenter ();
        itToLight.x = light->getCenter ().x - inter_point.x;
        itToLight.y = light->getCenter ().y - inter_point.y;
        itToLight.z = light->getCenter ().z - inter_point.z;
        normalize (&itToLight);
        Intersection * inter = intersectElement (itToLight, inter_point, true);
        if (inter == NULL || inter->object != light)
            continue;
        delete inter;

        
        // Diffuse light
        double k_d = mt.k_d;
        Color cd = light->getDiffuseLight (N, inter_point, k_d);
        c.r += cd.r;
        c.g += cd.g;
        c.b += cd.b;
        
        // Specular light
        double k_s = mt.k_s;
        double n = mt.n;
        R3Vector E;
        E.x = -V.x;
        E.y = -V.y;
        E.z = -V.z;
        cd = light->getSpecularLight (N, inter_point, E, k_s, n);
        c.r += cd.r;
        c.g += cd.g;
        c.b += cd.b;
    }

    double k_r = mt.k_r;
    if (k_r > 0)
    {
        // Get reflection intersection
        V.x = -V.x;
        V.y = -V.y;
        V.z = -V.z;
        double VN = prod (V, N);
        R3Vector R = N;
        R.x = 2 * VN * R.x - V.x;
        R.y = 2 * VN * R.y - V.y;
        R.z = 2 * VN * R.z - V.z;
        normalize (&R);
        Intersection * inter = intersectElement (R, inter_point, true);


        Color refColor;
        if (inter != NULL)
        {
            Object * reflectingObject = inter->object;
            R3Vector reflectingPoint = inter->point;
            if (reflectingObject->isLight () || level == MAX_REFLECTION)
            {
                refColor = reflectingObject->getColor ();
            }
            else
            {
                refColor = pointColor (reflectingObject, reflectingPoint, R, level + 1);
            }
        }

        c.r += k_r * refColor.r;
        c.g += k_r * refColor.g;
        c.b += k_r * refColor.b;
    }

    return c;
}


Intersection * intersectElement (R3Vector u, R3Vector p0, bool intersectLights)
{
    Intersection * nearestIntersection = NULL;
    double NIDistance = MAX_DEPTH * MAX_DEPTH;
    for (unsigned int i = 0; i < objs.size (); i++)
    {
        Object * object = objs[i];
        Intersection * intersection = object->intersect (u, p0);
        
        // If intersects nothing or intersects a light (and we are avoiding lights)
        // go to the next object
        if (intersection == NULL || 
           (!intersectLights && intersection->object->isLight ()))
            continue;

        double intDistance;
        R3Vector p0ToInt = intersection->point;
        p0ToInt.x = p0.x - p0ToInt.x;
        p0ToInt.y = p0.y - p0ToInt.y;
        p0ToInt.z = p0.z - p0ToInt.z;
        intDistance = norm (p0ToInt);

        if (nearestIntersection == NULL || intDistance - 1e-5 < NIDistance)
        {
            nearestIntersection = intersection;
            NIDistance = intDistance;
        }

    }
    return nearestIntersection;
}


void display (void)
{
    int i;
    int j;
    clearFramebuffer ();
    for (i = 0;i < ImageH; i++)
    {
        for (j = 0; j < ImageW; j++)
        {
            rayCast (i, j);
        }
    }
    drawit ();
}


void keyboard (unsigned char key, int x, int y)
{
    if (key == 'n')
    {
        state = 1 - state;
        lights.clear ();
        objs.clear ();
        init ();
        display ();
    }
}