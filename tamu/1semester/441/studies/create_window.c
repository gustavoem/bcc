#include <GL/glut.h>

void lineSegment (void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    
    glColor3f (.0, .4, .2);
    glBegin (GL_LINES);
        glVertex2i (10, 10);
        glVertex2i (10, 140);
    glEnd ();

    glFlush ();
}


void init ()
{
    glClearColor (1.0, 1.0, 1.0, .0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}


int main (int argc, char ** argv)
{
    glutInit (&argc, argv);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow ("Primeira janela");
    glutDisplayFunc (lineSegment);
    init ();
    glutMainLoop ();
    return 0;
}
