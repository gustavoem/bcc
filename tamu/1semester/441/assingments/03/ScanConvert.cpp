#include <GL/glut.h>
#include <fstream>
#include <math.h>
#include <vector>
#include <map>
#include <iostream>
#include "Polygon.h"

/******************************************************************
    Notes:
    Image size is 400 by 400 by default.  You may adjust this if
        you want to.
    You can assume the window will NOT be resized.
    Call clearFramebuffer to clear the entire framebuffer.
    Call setFramebuffer to set a pixel.  This should be the only
        routine you use to set the color (other than clearing the
        entire framebuffer).  drawit() will cause the current
        framebuffer to be displayed.
    As is, your scan conversion should probably be called from
        within the display function.  There is a very short sample
        of code there now.
    You may add code to any of the subroutines here,  You probably
        want to leave the drawit, clearFramebuffer, and
        setFramebuffer commands alone, though.
  *****************************************************************/

// frameBuffer matrix
//
float framebuffer[ImageH][ImageW][3];


// Stores the scan lines lists
//
static vector<Polygon *> polygons;


// Stores the state: 0 for defining polygons, 1 for clippping and 2 for waiting to define
// a polygon
//
static unsigned int my_state = 2;


// Stores the coordinates of the screen that received the last click
//
static unsigned int lcx;
static unsigned int lcy;


// Draws the scene
//
void drawit (void);


// Clears framebuffer to black
//
void clearFramebuffer ();


// Sets pixel x,y to the color RGB
// I've made a small change to this function to make the pixels match
// those returned by the glutMouseFunc exactly - Scott Schaefer 
//
void setFramebuffer (int x, int y, float R, float G, float B);


// Drawing callback
//
void display( void);


void init (void);


// Mouse callback
//
void mouse (int button, int state, int x, int y);


// Buffers all polygons to be drawed
//
void drawPolygons ();


//
//
bool comp_x (Edge e1, Edge e2);


// Draws a horizontal line into the buffer
//
void drawHorizontalLine (unsigned int x1, unsigned int x2, unsigned int y, color c);

int main(int argc, char** argv)
{
    glutInit (&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize (ImageW,ImageH);
    glutInitWindowPosition (500, 500);
    glutCreateWindow ("Gustavo Matos - Homework 2");
    init ();    
    glutDisplayFunc (display);
        glutMouseFunc (mouse);
    glutMainLoop ();
    return 0;
}


void drawit (void)
{
   glDrawPixels (ImageW, ImageH, GL_RGB, GL_FLOAT, framebuffer);
   glFlush ();
}


void clearFramebuffer ()
{
    int i, j;
    for (i = 0; i < ImageH; i++) 
        {
        for (j = 0; j < ImageW; j++) 
                {
            framebuffer[i][j][0] = 0.0;
            framebuffer[i][j][1] = 0.0;
            framebuffer[i][j][2] = 0.0;
        }
    }
}


void setFramebuffer (int x, int y, float R, float G, float B)
{
    // changes the origin from the lower-left corner to the upper-left corner
    y = ImageH - 1 - y;
    if (R <= 1.0)
        if (R >= 0.0)
            framebuffer[y][x][0] = R;
        else
            framebuffer[y][x][0] = 0.0;
    else
        framebuffer[y][x][0] = 1.0;
    if (G <= 1.0)
        if (G >= 0.0)
            framebuffer[y][x][1] = G;
        else
            framebuffer[y][x][1] = 0.0;
    else
        framebuffer[y][x][1]=1.0;
    if (B <= 1.0)
        if (B >= 0.0)
            framebuffer[y][x][2] = B;
        else
            framebuffer[y][x][2] = 0.0;
    else
        framebuffer[y][x][2] = 1.0;
}


void display( void)
{
    //The next two lines of code are for demonstration only.
    //They show how to draw a line from (0,0) to (100,100)
    int i;
    for(i = 0;i <= 100; i++) setFramebuffer(i,i,1.0,1.0,1.0);
    drawPolygons ();
    drawit ();
}

void init (void)
{
    clearFramebuffer ();
}


void mouse (int button, int state, int x, int y)
{
    std::cout << "\nButton pressed on <" << x << ", " << y << ">" << endl;
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
            {
                if (my_state == 2)
                {
                    my_state = 0;
                    color c;
                    c.r = 1.0 / (rand () / (float) RAND_MAX + 1);
                    c.g = 1.0 / (rand () / (float) RAND_MAX + 1);
                    c.b = 1.0 / (rand () / (float) RAND_MAX + 1);
                    Polygon * p = new Polygon (make_pair(x, y), c);
                    polygons.push_back (p);
                }
                else if (my_state == 0)
                {
                    polygons.back ()->newPoint (x, y);
                }
            }
            break;

        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
            {
                if (my_state == 0)
                {
                    my_state = 2;
                    polygons.back ()->closePolygon (x, y);
                    glutPostRedisplay ();
                }
            } 
            break;
    }
}

void drawPolygons ()
{
    for (unsigned int j = 0; j < polygons.size (); j++)
    {
        vector<Edge> active_edges;
        for (unsigned int i = 0; i < ImageH; i++)
        {
        
            vector<Edge> polygon_edges = polygons[j]->getScanLine (i);
            for (unsigned int k = 0; k < polygon_edges.size (); k++)
            {
                active_edges.push_back (polygon_edges[k]);
                cout << "Adding edge w/ maxy = " << polygon_edges[k].max_y << endl;
            }

            // Remove all edge that end at i
            for (unsigned int k = 0; k < active_edges.size (); k++)
                if (active_edges[k].max_y <= i)
                    active_edges.erase (active_edges.begin () + k);

            // Sorts every edge per current_x
            sort (active_edges.begin (), active_edges.end (), comp_x);

            // Now draw every odd interval of current_x
            color c = polygons[j]->getColor ();
            cout << "\nColorrrrr" << c.r << " " << c.g << " " << c.b << endl;
            for (unsigned int k = 0; k + 1 < active_edges.size (); k += 2)
                drawHorizontalLine (active_edges[k].current_x, active_edges[k + 1].current_x, i, c);

            // Updates current_x
            for (unsigned int k = 0; k < active_edges.size (); k++)
                active_edges[k].current_x += active_edges[k].x_increment; 
        }
    }
}

bool comp_x (Edge e1, Edge e2) { return (e1.current_x < e2.current_x); }

void drawHorizontalLine (unsigned int x1, unsigned int x2, unsigned int y, color c)
{
    for (unsigned int i = x1; i < x2; i++) setFramebuffer(i,y,c.r,c.g,c.b);
}