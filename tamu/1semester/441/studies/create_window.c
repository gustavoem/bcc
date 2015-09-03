#include <GL/glut.h>

void lineSegment (void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glFlush ();
}


void init ()
{
    glClearColor (1.0, 1.0, 1.0, .0);

}


int main (int argc, char ** argv)
{
    glutInit (&argc, argv);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow ("Primeira janela");
    glutDisplayFunc (lineSegment);
    glutMainLoop ();
    return 0;
}
