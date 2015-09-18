# include <GL/glut.h>

#define cos30 0.866

void init (void)
{
    // Set display-window color to white.
    glClearColor (.0, .0, .0, .0);
    // Set projection parameters.
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 1000.0, 0.0, 500.0);
}

void lineSegment (void)
{
    float r = 200;
    float h = r * cos30;
    // Clears display with color defined with glClearColor
    glClear (GL_COLOR_BUFFER_BIT);
    glLineWidth (10.0);
    // Sets color to green
    glBegin (GL_LINES);
        glColor3f (1, 1, 1);
        glVertex2i (500 - r, 250);
        glVertex2i (500 - r/2, 250 + h);
        
        glColor3f (.0, .7, .0);
        glVertex2i (500 - r/2, 250 + h);
        glVertex2i (500 + r/2, 250 + h);
        
        glColor3f (.5, .0, .7);
        glVertex2i (500 + r/2, 250 + h);
        glVertex2i (500 + r, 250);
        
        glColor3f (1.0, .5, .0);
        glVertex2i (500 + r, 250);
        glVertex2i (500 + r/2, 250 - h);
        
        glColor3f (.5, .3, .0);
        glVertex2i (500 + r/2, 250 - h);
        glVertex2i (500 - r/2, 250 - h);
        
        glColor3f (.85, .85, .0);
        glVertex2i (500 - r/2, 250 - h);
        glVertex2i (500 - r, 250);
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
    glutInitWindowSize (1000, 500);
    glutCreateWindow ("Gustavo - Assignment 1");  
    init ( );

    // Set drawing callback
    glutDisplayFunc (lineSegment);

    // Starts glut app
    glutMainLoop ( );
    return 0;
}
