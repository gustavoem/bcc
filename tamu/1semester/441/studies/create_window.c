#include <GL/glut.h>

void lineSegment (void)
{
    return;
}


int main (int argc, char ** argv)
{
    glutInit (&argc, argv);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Primeira janela");
    glutDisplayFunc (lineSegment);
    glutMainLoop ();
    return 0;
}
