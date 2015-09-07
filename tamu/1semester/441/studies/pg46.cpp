#define GLEW_STATIC
# include <GL/glew.h>
# include <GL/glut.h>
void init (void)
{
    // Set display-window color to white.
    glClearColor (1.0, 1.0, 1.0, 0.0);
    // Set projection parameters.
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}

void lineSegment (void)
{
    // Clears display with color defined with glClearColor
    glClear (GL_COLOR_BUFFER_BIT);

    // Sets color to green
    glColor3f (0.0, 0.4, 0.2);
    glBegin (GL_LINES);
        glVertex2i (180, 15);
        glVertex2i (10, 145);
    glEnd ( );
    glFlush ( );
}


int main (int argc, char** argv)
{
    // Initialize glut
    glutInit (&argc, argv);
    
    // Window settings
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50, 100);
    glutInitWindowSize (400, 300);
    glutCreateWindow ("An Example OpenGL Program");  
    init ( );

    // Set drawing callback
    glutDisplayFunc (lineSegment);

    // Starts glut app
    glutMainLoop ( );
    return 0;
}
