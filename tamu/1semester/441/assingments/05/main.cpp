#include <GL/glut.h>

#include "global.h"
#include "Sphere.h"
#include "Light.h" 
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


// Lights
//
Light * light1;


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
    center.x = 500;
    center.y = 500;
    center.z = FILM_WALL_Z + 100;
    Material material;
    material.k_a = 0.2;
    material.k_d = 0.5;
    material.k_s = 0.5;
    Sphere * sphere1 = new Sphere (center, 50, color, material);
    objs.push_back (sphere1);
    
    color.r = 1;
    color.g = 0;
    color.b = 1;
    center.x = 400;
    center.y = 400;
    center.z = FILM_WALL_Z - 100;
    light1 = new Light (center, color);

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
            return;

        Color c;
        c = intersection->first;
        // Ambient light
        Material mt = object->getMaterial ();
        double k_a = mt.k_a;
        c.r *= light1->getIntensity ().r  * k_a;
        c.g *= light1->getIntensity ().g  * k_a;
        c.b *= light1->getIntensity ().b  * k_a;

        // Diffuse light
        double k_d = mt.k_d;
        R3Vector N = object->getNormal (intersection->second);
        Color cd = light1->getDiffuseLight (N, intersection->second);
        c.r += cd.r * k_d;
        c.g += cd.g * k_d;
        c.b += cd.b * k_d;

        float z = intersection->second.z;
        setFramebuffer (x, y, c.r, c.g, c.b, z);
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