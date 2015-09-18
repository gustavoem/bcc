#include <iostream>
#include <GL/glut.h>
#include <cmath>

#define WINDOWSX 500
#define WINDOWSY 500
#define STD_SPIN_RATE 5
#define STD_COLOR_INTENSITY .5
#define PI 3.14159265

static GLfloat spin = 0.0;
static int hx;
static int hy;
static float spin_rate = 2.0;
static float color_intensity = 0.5;
static float cR = 1, cG = 1, cB = 1;
static GLfloat pol_x = 0;
static GLfloat pol_y = 0;

// 1 vertice only
// 2 set of lines
// 3 full polygon
static int viewmode = 3;

void init (void)
{
    glClearColor (color_intensity * cR, color_intensity * cG, color_intensity * cB, 0.0);
    glShadeModel (GL_FLAT);
    glPointSize (5.0);
    glLineWidth (5.0);
}


void drawPolygon ()
{
    
    glPushMatrix ();
    glTranslatef (pol_x, pol_y, 1);
    switch (viewmode)
    {
        case 1:
            glBegin (GL_POINTS);
            break;
        case 2:
            glBegin (GL_LINE_LOOP);
            break;
        case 3:
            glBegin (GL_POLYGON);
            break;
    }
    glVertex2f (-10.0, .0);
    glVertex2f (-20, 10.0);
    glVertex2f (10.0, 10.0);
    glEnd ();
    
    glPopMatrix ();
}



void display (void)
{
    float r = cR * color_intensity;
    float g = cG * color_intensity;
    float b = cB * color_intensity;
    glClear (GL_COLOR_BUFFER_BIT);
    glPushMatrix ();
    glRotatef (spin, 0.0, 0.0, 1.0);
    glColor3f (1 - r /.5, 1 - g/.5, 1 - b/.5);
    drawPolygon ();
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
    switch (button) 
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) 
            { 
                glutIdleFunc (spinClockwise);
            }
            else 
                glutIdleFunc (NULL);
                
            break;

        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc (spinCounterClockwise);
            else
                glutIdleFunc (NULL);
            break;

        case GLUT_MIDDLE_BUTTON:
            if (state == GLUT_UP)
            {
                GLfloat dx = ((x - hx) / (float) WINDOWSX) * 100;
                GLfloat dy = -((y - hy) / (float) WINDOWSY) * 100;
                GLfloat norm = sqrt (dx * dx + dy * dy);
                GLfloat angle;
                if (dx < .1 && dx > -.1)
                    if (dy < 0)
                        angle = PI/2; 
                    else
                        angle = -PI/2;
                else
                    angle = atan2 (dy, dx);
            

                GLfloat new_dx = norm * cos ( -(spin * PI / 180.0) + angle);
                GLfloat new_dy = norm * sin ( -(spin * PI / 180.0) + angle);
                pol_x += new_dx;
                pol_y += new_dy;
            }
            break;
            
        default:
            break;
    }
    
    if (state == GLUT_DOWN)
    {
        hx = x;
        hy = y;
    }
    else
    {
        spin_rate = 1;
        color_intensity = STD_COLOR_INTENSITY;
    }
    glutPostRedisplay ();
}


void mouse_move (int x, int y)
{
    spin_rate = STD_SPIN_RATE + pow (2, (hy - y) / 50);
    color_intensity = (1 + (x - hx) / (float) WINDOWSX) / 2;
    glClearColor (color_intensity * cR, color_intensity * cG, color_intensity * cB, 0.0);
    glutPostRedisplay ();
}


void keyboard (unsigned char key, int x, int y)
{
    switch (key) 
    {
        case 'c':
            cR = 0;
            cG = 1;
            cB = 1;
            break;

        case 'm':
            cR = 1;
            cG = 0;
            cB = 1;
            break;

        case 'y':
            cR = 1;
            cG = 1;
            cB = 0;
            break;

        case 'w':
            cR = cG = cB = 1;
            break;
        case '1':
            viewmode = 1;
            break;
            
        case '2':
            viewmode = 2;
            break;

        case '3':
            viewmode = 3;
            break;

        default:
            break;
    }
    glClearColor (color_intensity * cR, color_intensity * cG, color_intensity * cB, 0.0);
    glutPostRedisplay ();
}

/*
 * * Request double buffer display mode.
 * * Register mouse input callback functions
 * */
int main (int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (WINDOWSX, WINDOWSY);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Gustavo Estrela - Assignment 2");
    init ();
    glutDisplayFunc (display);
    glutReshapeFunc (reshape);
    glutMouseFunc (mouse);
    glutMotionFunc (mouse_move);
    glutKeyboardFunc(keyboard);
    glutMainLoop ();
    return 0;
}
