
/* Copyright (c) Mark J. Kilgard, 1997. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */

/* This program was requested by Patrick Earl; hopefully someone else
   will write the equivalent Direct3D immediate mode program. */

#include <GL/glut.h>
#include <iostream>
#include "Fly.h"

#define WINDOW_X 700
#define WINDOW_Y 700

using namespace std;

// Used to define a zoom, moving the near plan closer to the object
//
float zoom = 0;

// Used to move the eyeposition
//
float eyex;
float eyey;


Fly fly;

void display (void);

void init (void);

void mouse (int button, int state, int x, int y);

void mouseMove (int x, int y);

void applyZoom ();


int main(int argc, char **argv)
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (WINDOW_X, WINDOW_X);
  glutCreateWindow ("Assignment 3");
  glutDisplayFunc (display);
  glutMouseFunc (mouse);
  glutPassiveMotionFunc (mouseMove);
  init();
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}


void display (void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    applyZoom ();
    glColor4f (.5, .5, .1, .5);

    glPushMatrix ();
    glTranslatef (0.0, 0.0, 10.0);
    fly.draw ();
    glutSolidCube (2);
    glPopMatrix ();

    glutSwapBuffers ();
}


void init (void)
{
    glClearColor (208.0 / 255, 258.0 / 255, 1, 1);

//    /* Use depth buffering for hidden surface elimination. */
//    glEnable (GL_DEPTH_TEST);

    // Projection Matrix
    glMatrixMode (GL_PROJECTION);
    glFrustum (-1, 1, -1, 1, 1, 100);

    glMatrixMode (GL_MODELVIEW);
    gluLookAt (0.0, 0.0, 0.0,  /* eye is at (0,0,0) */
        0.0, 0.0, 10.0,        /* center is at (0,0,10) */
        0.0, 1.0, 0.0);        /* up is in positive Y direction */
}


void mouse (int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            break;

        case GLUT_RIGHT_BUTTON:
            break;

        case 3:
            // if (state == GLUT_UP) return;
            zoom += 0.05;
            if (zoom > 2) zoom = 2;
            break;

        case 4:
            // if (state == GLUT_UP) return;
            zoom -= 0.05;
            if (zoom < 0) zoom = 0;
            break;
    
    }
    glutPostRedisplay ();
}


void mouseMove (int x, int y)
{
    cout << "Moving mouse to x:" << x << " y:" << y << endl; 
    float x_p = (float) x / WINDOW_X;
    float y_p = (float) y / WINDOW_Y;

    eyex = x_p * 10 - 5;
    eyey = y_p * 10 - 5;


    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt (eyex, eyey, 0.0,  /* eye is at (eyex,eyey,0) */
        0.0, 0.0, 10.0,        /* center is at (0,0,10) */
        0.0, 1.0, 0.0);        /* up is in positive Y direction */

    glutPostRedisplay ();
}


// We apply zoom by translating the near plan nearer the object
//
void applyZoom ()
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glFrustum (-1, 1, -1, 1, 1 + zoom, 100);
    glMatrixMode (GL_MODELVIEW);
}