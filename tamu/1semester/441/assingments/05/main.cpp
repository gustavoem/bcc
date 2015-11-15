#include <GL/glut.h>
#include <fstream>
#include <math.h>

/******************************************************************
    Notes:
    This is the same utility as in the earlier homework assignment.
    Image size is 400 by 400 by default.  You may adjust this if
        you want to.
    You can assume the window will NOT be resized.
    Call clearFramebuffer to clear the entire framebuffer.
    Call setFramebuffer to set a pixel.  This should be the only
        routine you use to set the color (other than clearing the
        entire framebuffer).  drawit() will cause the current
        framebuffer to be displayed.
    As is, your ray tracer should probably be called from
        within the display function.  There is a very short sample
        of code there now.  You can replace that with a call to a
        function that raytraces your scene (or whatever other
        interaction you provide.
    You may add code to any of the subroutines here,  You probably
        want to leave the drawit, clearFramebuffer, and
        setFramebuffer commands alone, though.
  *****************************************************************/

#define ImageW 800
#define ImageH 800

float framebuffer[ImageH][ImageW][3];

struct color 
{
    float r, g, b;      // Color (R,G,B values)
};


// Draws the scene
void drawit (void)
{
   glDrawPixels (ImageW,ImageH,GL_RGB,GL_FLOAT,framebuffer);
   glFlush ();
}

// Clears framebuffer to black
void clearFramebuffer()
{
    int i, j;

    for (i = 0;i < ImageH; i++)
    {
        for (j = 0;j < ImageW; j++)
        {
            framebuffer[i][j][0] = 0.0;
            framebuffer[i][j][1] = 0.0;
            framebuffer[i][j][2] = 0.0;
        }
    }
}

// Sets pixel x,y to the color RGB
void setFramebuffer(int x, int y, float R, float G, float B)
{
    if (R <= 1.0)
        if (R >= 0.0)
            framebuffer[x][y][0] = R;
        else
            framebuffer[x][y][0] = 0.0;
    else
        framebuffer[x][y][0] = 1.0;

    if (G <= 1.0)
        if (G >= 0.0)
            framebuffer[x][y][1] = G;
        else
            framebuffer[x][y][1] = 0.0;
    else
        framebuffer[x][y][1] = 1.0;

    if (B <= 1.0)
        if (B >= 0.0)
            framebuffer[x][y][2] = B;
        else
            framebuffer[x][y][2] = 0.0;
    else
        framebuffer[x][y][2] = 1.0;
}

void display(void)
{
    //The next two lines of code are for demonstration only.
    //They show how to draw a line from (0,0) to (100,100)
    int i;
    
    for (i = 0;i <= 100; i++)
        setFramebuffer (i, i, 1.0, 1.0, 1.0);

    drawit ();
}

void init(void)
{
    clearFramebuffer ();
}

int main(int argc, char** argv)
{
    glutInit (&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize (ImageW,ImageH);
    glutInitWindowPosition (100,100);
    glutCreateWindow ("Gustavo Estrela - Assignment 5");
    init ();    
    glutDisplayFunc (display);
    glutMainLoop ();
    return 0;
}