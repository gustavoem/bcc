#include <GL/glut.h>
#include <fstream>


/******************************************************************
    Notes:
    This is the same utility as in the earlier homework assignment.
    Image size is 400 by 400 by default.  You may adjust this if
        you want to.
    You can assume the window will NOT be resized.
    Call clearFramebuffer to clear the entire framebuffer.
    Call setFramebuffer to set a pixel.  This should be the only
        routine you use to set the color (other than clearing the
        entire framebuffer).  drawit() will cause the current
        framebuffer to be displayed.
    As is, your ray tracer should probably be called from
        within the display function.  There is a very short sample
        of code there now.  You can replace that with a call to a
        function that raytraces your scene (or whatever other
        interaction you provide.
    You may add code to any of the subroutines here,  You probably
        want to leave the drawit, clearFramebuffer, and
        setFramebuffer commands alone, though.
  *****************************************************************/

#define ImageW 800
#define ImageH 800
#define FILM_WALL_Z 1000
#define MAX_DEPTH 10000

#include "global.h"
#include "Sphere.h"
#include "Light.h"        

float framebuffer[ImageH][ImageW][3];

float zbuffer[ImageH][ImageW];


// Elements to be drawn
//
Sphere * sphere1;
Sphere * sphere2;

Light * light1;



Vector eye;


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
    init ();    
    glutDisplayFunc (display);
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
    eye.x = 0;
    eye.y = 0;
    eye.z = 0;

    Color color;
    color.r = 1;
    color.g = 0;
    color.b = 0;
    Vector center;
    center.x = 800;
    center.y = 800;
    center.z = FILM_WALL_Z + 100;
    sphere1 = new Sphere (center, 50, color, .1, .15);
    
    color.r = 1;
    color.g = 0;
    color.b = 1;
    center.y = 1000;
    center.z = FILM_WALL_Z;
    light1 = new Light (center, color);

    clearFramebuffer ();
}


void intersectElements (int x, int y)
{
    // Ray tracing vector
    Vector u;
    u.x = x - eye.x;
    u.y = y - eye.y;
    u.z = FILM_WALL_Z - eye.z;
    double u_norm = u.x * u.x + u.y * u.y + u.z * u.z;
    u_norm = sqrt (u_norm);
    u.x /= u_norm;
    u.y /= u_norm;
    u.z /= u_norm;


    pair<Color, Vector> * intersection;
    intersection = sphere1->intersect (u, eye);
    if (intersection == NULL)
        return;

    Color c;
    c = intersection->first;
    // Ambient light
    double k_a = sphere1->getAmbientCoef ();
    c.r *= light1->getIntensity ().r  * k_a;
    c.g *= light1->getIntensity ().g  * k_a;
    c.b *= light1->getIntensity ().b  * k_a;

    // Diffuse light
    double k_d = sphere1->getDiffuseCoef ();
    Vector N = sphere1.getNormal (intersection->second);
    light1.get


    float z = intersection->second.z;
    setFramebuffer (x, y, c.r, c.g, c.b, z);
    delete intersection;
}


void display (void)
{
    int i;
    int j;

    for (i = 0;i < ImageH; i++)
    {
        for (j = 0; j < ImageW; j++)
        {
            intersectElements (i, j);
        }
    }

    drawit ();
}