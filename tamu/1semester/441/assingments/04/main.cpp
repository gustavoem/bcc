
/* Copyright (c) Mark J. Kilgard, 1997. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */

/* This program was requested by Patrick Earl; hopefully someone else
   will write the equivalent Direct3D immediate mode program. */

#include <GL/glut.h>
#include <iostream>

using namespace std;

float zoom = 0;

void mouse (int button, int state, int x, int y);

void applyZoom ();

void display (void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    applyZoom ();
    glColor4f (.5, .5, .1, .5);

    glPushMatrix ();
    /* Adjust cube position to be asthetic angle. */
    glTranslatef (0.0, 0.0, 5.0);
    glRotatef (60, 1.0, 0.0, 0.0);
    glRotatef (-20, 0.0, 0.0, 1.0);
    glutSolidCube (1);
    glPopMatrix ();

    glutSwapBuffers ();
}


void init (void)
{
    glClearColor (208.0 / 255, 258.0 / 255, 1, 1);
    /* Enable a single OpenGL light. */
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    //glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHTING);

    /* Use depth buffering for hidden surface elimination. */
    glEnable (GL_DEPTH_TEST);

    /* Setup the view of the cube. */
    glMatrixMode (GL_PROJECTION);
    // gluPerspective( /* field of view in degree */ 40.0,
    //    aspect ratio  1.0,
    //   /* Z near */ 1.0, /* Z far */ 10.0);
    glFrustum (-1, 1, -1, 1, 1, 10);

    glMatrixMode (GL_MODELVIEW);
    gluLookAt (0.0, 0.0, 0.0,  /* eye is at (0,0,0) */
        0.0, 0.0, 10.0,      /* center is at (0,0,10) */
        0.0, 1.0, 0.);      /* up is in positive Y direction */
}




int main(int argc, char **argv)
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow ("Assignment 3");
  glutDisplayFunc (display);
  glutMouseFunc (mouse);
  init();
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
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
            if (state == GLUT_UP) return;
            cout << "Scroll up!" << endl;
            zoom += 0.2;
            if (zoom > 2) zoom = 2;
            break;
        case 4:
            if (state == GLUT_UP) return;
            cout << "Scroll down!" << endl;
            zoom -= 0.2;
            if (zoom < 0) zoom = 0;
            break;
    }
    glutPostRedisplay ();
}

void applyZoom ()
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    cout << "zoom value: " << zoom;
    glFrustum (-1, 1, -1, 1, 1 + zoom, 10);
    glMatrixMode (GL_MODELVIEW);
}