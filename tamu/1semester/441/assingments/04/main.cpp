#include <GL/glut.h>

static int shoulder = 0, elbow = 0;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef (-1.0, 0.0, 0.0);
    glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
    glTranslatef (1.0, 0.0, 0.0);
    glutSolidCube (2.0); /* shoulder */
    glTranslatef (1.0, 0.0, 0.0);
    glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
    glTranslatef (1.0, 0.0, 0.0);
    glutSolidCube(2.0); /* elbow */
    glPopMatrix();
    glFlush();
}


void myinit (void)
{
    glShadeModel (GL_FLAT);
}


void myReshape(GLsizei w, GLsizei h)
{
    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    glTranslatef (0.0, 0.0, -5.0);
}


int main(int argc, char** argv)
{
    glutInit (&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (500, 500);
    glutCreateWindow ("Gustavo Matos - Homework 2");
    myinit ();
    glutReshapeFunc (myReshape);
    glutDisplayFunc (display);
    glutMainLoop ();
}