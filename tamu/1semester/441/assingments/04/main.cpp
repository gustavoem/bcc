
/* Copyright (c) Mark J. Kilgard, 1997. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */

/* This program was requested by Patrick Earl; hopefully someone else
   will write the equivalent Direct3D immediate mode program. */

#include <GL/glut.h>
#include <iostream>
#include "Ant.h"

#define WINDOW_X 700
#define WINDOW_Y 700

using namespace std;

// Used to determine if ant is walking or not
//
bool walking = false;

// Used to define a zoom, moving the near plan closer to the object
//
float zoom = 0;


// Used to rotate around our insect
//
int rotation = 0;


// Used to move the eyeposition
//
float eyex;
float eyey;

// Our ant object
//
Ant ant;


void display (void);


void init (void);


void mouse (int button, int state, int x, int y);


void mouseMove (int x, int y);


// Callback for special keys from keyboard
//
void SpecialFunc (int key, int x, int y);


// Keyboard callback
//
void keyboard (unsigned char key, int x, int y);


// We apply zoom by translating the near plan nearer the object
//
void applyZoom ();


// Apply rotation
//
void applyRotation ();


// Makes ant walk
//
void walkAnt ();


int main(int argc, char **argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (WINDOW_X, WINDOW_X);
    glutCreateWindow ("Assignment 4");
    glutDisplayFunc (display);
    glutMouseFunc (mouse);
    glutPassiveMotionFunc (mouseMove);
    glutKeyboardFunc (keyboard);
    glutSpecialFunc (SpecialFunc);
    init ();
    glutMainLoop ();
    return 0;             /* ANSI C requires main to return int. */
}


void display (void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix ();

    if (walking)
        walkAnt ();

    // applies rotation
    applyRotation ();

    // applies zoom
    applyZoom ();

    glPushMatrix ();
    glTranslatef (0.0, 0.0, 10.0);
    ant.draw ();
    glPopMatrix ();

    glutSwapBuffers ();
    glPopMatrix ();
}


void init (void)
{
    glClearColor (208.0 / 255, 258.0 / 255, 1, 1);
    
    // Enables culling
    glCullFace (GL_BACK); 
    glEnable(GL_CULL_FACE);

    // Enables z-buffering
    glEnable (GL_DEPTH_TEST);

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
            if (zoom > 3) zoom = 3;
            break;

        case 4:
            // if (state == GLUT_UP) return;
            zoom -= 0.05;
            if (zoom < 0) zoom = 0;
            break;
    
    }
}


void mouseMove (int x, int y)
{
    float x_p = (float) x / WINDOW_X;
    float y_p = (float) y / WINDOW_Y;

    eyex = x_p * 20 - 5;
    eyey = y_p * 20 - 5;


    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt (eyex, eyey, 0.0,  /* eye is at (eyex,eyey,0) */
        0.0, 0.0, 10.0,        /* center is at (0,0,10) */
        0.0, 1.0, 0.0);        /* up is in positive Y direction */

    glutPostRedisplay ();
}


void SpecialFunc (int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            rotation += 5;
            break;
        case GLUT_KEY_RIGHT:
            rotation -= 5;
            break;
    }
    rotation = rotation % 361;
    glutPostRedisplay ();
}


void keyboard (unsigned char key, int x, int y)
{
    switch (key) 
    {
        case 'n':
            ant.selectNextMember ();
            break;

        case 'w':
            ant.rotateMember (1, 0);
            break;

        case 's':
            ant.rotateMember (-1, 0);
            break;

        case 'a':
            ant.rotateMember (0, 1);
            break;

        case 'd':
            ant.rotateMember (0, -1);
            break;

        case 'g':
            walking = !walking;
    }
    glutPostRedisplay ();
}


void applyZoom ()
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glFrustum (-1, 1, -1, 1, 1 + zoom, 100);
    glMatrixMode (GL_MODELVIEW);
}


void applyRotation ()
{
    glTranslatef (0, 0, 10);
    glRotatef ((float) rotation, 0.0, 1.0, 0);
    glTranslatef (0, 0, -10);
}


void walkAnt ()
{
    ant.walkStep ();
    glutPostRedisplay ();
}