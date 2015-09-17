#include <iostream>
#include <GL/glut.h>
#include <cmath>

#define STD_SPIN_RATE 5

static GLfloat spin = 0.0;
static int hx;
static int hy;
static float spin_rate = 2.0;

void init (void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}


void display (void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glPushMatrix ();
    glRotatef (spin, 0.0, 0.0, 1.0);
    glColor3f (1.0, 1.0, 1.0);
    glBegin (GL_POLYGON);
        glVertex2f (-10.0, .0);
        glVertex2f (-20, 10.0);
        glVertex2f (10.0, 10.0);
    glEnd ();
    glPopMatrix ();
    glutSwapBuffers ();
}


void spinDisplay (int orientation)
{
    spin = spin + orientation * (spin_rate + STD_SPIN_RATE);
    if (spin > 360.0)
        spin = spin - 360.0;
    if (spin < 0)
        spin = spin + 360.0;
    glutPostRedisplay ();
}


void spinClockwise ()
{
    spinDisplay (1);
}


void spinCounterClockwise ()
{
    spinDisplay (-1);
}


void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho (-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}


void mouse (int button, int state, int x, int y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)  
                glutIdleFunc (spinClockwise);
            else
                glutIdleFunc (NULL);

        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc (spinCounterClockwise);
            else
                glutIdleFunc (NULL);

        default:
            if (state == GLUT_DOWN)
            {
                hx = x;
                hy = y;
            }
            else
                spin_rate = 1;
    }
}

void mouse_move (int x, int y)
{
    spin_rate = pow (1.5, (hy - y) / 50 );
}


/*
 * * Request double buffer display mode.
 * * Register mouse input callback functions
 * */
int main (int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Gustavo Estrela - Assignment 2");
    init ();
    glutDisplayFunc (display);
    glutReshapeFunc (reshape);
    glutMouseFunc (mouse);
    glutMotionFunc (mouse_move);
    glutMainLoop ();
    return 0;
}
