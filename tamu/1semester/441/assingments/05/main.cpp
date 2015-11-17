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


Object * sphere_add;


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
Intersection * intersectElements (R3Vector u, R3Vector p0, bool intersectLights);

int main (int argc, char** argv)
{
    glutInit (&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize (ImageW,ImageH);
    glutInitWindowPosition (100,100);
    glutCreateWindow ("Gustavo Estrela - Assignment 5");
    glutDisplayFunc (display);
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
    Sphere * sphere1 = new Sphere (center, 100, color, material);
    objs.push_back (sphere1);
    sphere_add = sphere1;


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
    center.z = FILM_WALL_Z + 1000;
    normal.x = 0;
    normal.y = 0;
    normal.z = -1;
    Plane * plane5 = new Plane (center, color, material, normal);
    objs.push_back (plane5);

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
    
    Intersection * inter = intersectElements (u, eye, false);
    if (inter == NULL) return;

    Object * obj = inter->object;
    // if (obj->getMaterial ().k_s == 0.6)
    //     cout << "Hum, intersection on the spheaaare" << obj << endl;
    Color c = inter->color;
    R3Vector inter_point = inter->point;
    delete inter;

    // Ambient light
    Material mt = obj->getMaterial ();
    double k_a = mt.k_a;
    c.r *= ambent_light->getIntensity ().r  * k_a;
    c.g *= ambent_light->getIntensity ().g  * k_a;
    c.b *= ambent_light->getIntensity ().b  * k_a;

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
        inter = intersectElements (itToLight, inter_point, true);

        if (inter->object != light)
        {    
        //     if (obj->getMaterial ().k_s == 0.6)
        //     {
        //         cout << "Intersected to: " << inter->object << endl;
        //         cout.flush ();
        //     }
            continue;
        }

        R3Vector N = obj->getNormal (inter_point);
        
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
        E.x = -u.x;
        E.y = -u.y;
        E.z = -u.z;
        cd = light->getSpecularLight (N, inter_point, E, k_s, n);
        c.r += cd.r;
        c.g += cd.g;
        c.b += cd.b;
    }


    setFramebuffer (y, x, c.r, c.g, c.b);
}



Intersection * intersectElements (R3Vector u, R3Vector p0, bool intersectLights)
{
    Intersection * nearestIntersection = NULL;
    double NIDistance = MAX_DEPTH * MAX_DEPTH;
    for (unsigned int i = 0; i < objs.size (); i++)
    {
        Object * object = objs[i];
        Intersection * intersection = object->intersect (u, p0);
        
        // If intersects nothing or intersects a light go to the next object
        if (intersection == NULL)
            continue;

        double intDistance;
        R3Vector p0ToInt = intersection->point;
        p0ToInt.x = p0.x - p0ToInt.x;
        p0ToInt.y = p0.y - p0ToInt.y;
        p0ToInt.z = p0.z - p0ToInt.z;
        intDistance = norm (p0ToInt);
        if (object == sphere_add)
        {
            // cout << "Nearest one: " << NIDistance << endl;
            // cout << "Intersected to an obj " << object << " distance: " << intDistance << endl; 
            // cout << "teste: " << (intDistance < NIDistance) << endl;
        }
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