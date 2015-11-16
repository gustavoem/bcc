#include <GL/glut.h>

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

float zbuffer[ImageH][ImageW];


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
void intersectElements (int x, int y);


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

            zbuffer[i][j] = MAX_DEPTH;
        }
    }
}


void setFramebuffer (int x, int y, float R, float G, float B, float z)
{
    if (zbuffer[x][y] < z)
         return;
    zbuffer[x][y] = z;

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
    color.r = 1;
    color.g = 0;
    color.b = 0;
    R3Vector center;
    center.x = 100;
    center.y = 100;
    center.z = FILM_WALL_Z + 200;
    Material material;
    material.k_a = 0.2;
    material.k_d = 0.3;
    material.k_s = 0.2;
    material.n = 1;
    Sphere * sphere1 = new Sphere (center, 100, color, material);
    objs.push_back (sphere1);



    // Walls
    color.r = .5;
    color.g = .7;
    color.b = .7;
    center.x = 0;
    center.y = 0;
    center.z = FILM_WALL_Z;
    material.k_a = 0.2;
    material.k_d = 0.6;
    material.k_s = 0.4;
    R3Vector normal;
    normal.x = 1;
    normal.y = 0;
    normal.z = 0;
    material.n = 10000;
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
    Sphere * sphere2 = new Sphere (center, 10, color, material);
    Light * light1 = new Light (center, color);
    lights.push_back (light1);
    objs.push_back (sphere2);

    color.r = 255 / 255;
    color.g = 100.0 / 255;
    color.b = 100.0 / 255;
    center.x = 400;
    center.y = 110;
    center.z = FILM_WALL_Z + 100;
    material.k_a = 1;
    material.k_d = 0;
    material.k_s = 0;
    Sphere * sphere3 = new Sphere (center, 10, color, material);
    Light * light2 = new Light (center, color);
    lights.push_back (light2);
    objs.push_back (sphere3);

    color.r = 1;
    color.g = 1;
    color.b = 1;
    center.x = 400;
    center.y = 0;
    center.z = 0;
    ambent_light = new Light (center, color);

    clearFramebuffer ();
}


void intersectElements (int x, int y)
{
    // Ray tracing R3Vector
    R3Vector u;
    u.x = x - eye.x;
    u.y = y - eye.y;
    u.z = FILM_WALL_Z - eye.z;
    normalize (&u);

    for (unsigned int i = 0; i < objs.size (); i++)
    {
        Object * object = objs[i];
        pair<Color, R3Vector> * intersection;
        intersection = object->intersect (u, eye);
        if (intersection == NULL)
            continue;

        Color c;
        c = intersection->first;
        // Ambient light
        Material mt = object->getMaterial ();
        double k_a = mt.k_a;
        c.r *= ambent_light->getIntensity ().r  * k_a;
        c.g *= ambent_light->getIntensity ().g  * k_a;
        c.b *= ambent_light->getIntensity ().b  * k_a;

        for (unsigned int j = 0; j < lights.size (); j++)
        {
            Light * light = lights[j];
            R3Vector N = object->getNormal (intersection->second);
            // Diffuse light
            double k_d = mt.k_d;
            Color cd = light->getDiffuseLight (N, intersection->second, k_d);
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
            cd = light->getSpecularLight (N, intersection->second, E, k_s, n);
            c.r += cd.r;
            c.g += cd.g;
            c.b += cd.b;
        }

        float z = intersection->second.z;
        setFramebuffer (y, x, c.r, c.g, c.b, z);
        delete intersection;
    }
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
            intersectElements (i, j);
        }
    }
    drawit ();
}