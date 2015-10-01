#include<GL/glut.h>
#include<fstream>
#include<math.h>
#include<vector>
#include<map>

/******************************************************************
	Notes:
	Image size is 400 by 400 by default.  You may adjust this if
		you want to.
	You can assume the window will NOT be resized.
	Call clearFramebuffer to clear the entire framebuffer.
	Call setFramebuffer to set a pixel.  This should be the only
		routine you use to set the color (other than clearing the
		entire framebuffer).  drawit() will cause the current
		framebuffer to be displayed.
	As is, your scan conversion should probably be called from
		within the display function.  There is a very short sample
		of code there now.
	You may add code to any of the subroutines here,  You probably
		want to leave the drawit, clearFramebuffer, and
		setFramebuffer commands alone, though.
  *****************************************************************/

#define ImageW 400
#define ImageH 400

using namespace std;



// frameBuffer matrix
//
float framebuffer[ImageH][ImageW][3];


// Color struct
//
struct color {
    float r, g, b;		// Color (R,G,B values)
};


// Polygon struct
//
struct polygon {
    color c;
    map<unsigned int, vector<unsigned int> > scan_lines;
};


// Stores the scan lines lists
//
vector<polygon> polygons;


// Stores the state: 0 for defining polygons, 1 for clippping and 2 for waiting to define
// a polygon
//
unsigned int my_state;


// Stores the coordinates of the screen that received the last click
//
unsigned int lcx;
unsigned int lcy;


// Draws the scene
//
void drawit (void)
{
   glDrawPixels (ImageW, ImageH, GL_RGB, GL_FLOAT, framebuffer);
   glFlush ();
}


// Clears framebuffer to black
//
void clearFramebuffer ()
{
	int i, j;
	for (i = 0; i < ImageH; i++) 
        {
		for (j = 0; j < ImageW; j++) 
                {
			framebuffer[i][j][0] = 0.0;
			framebuffer[i][j][1] = 0.0;
			framebuffer[i][j][2] = 0.0;
		}
	}
}


// Sets pixel x,y to the color RGB
// I've made a small change to this function to make the pixels match
// those returned by the glutMouseFunc exactly - Scott Schaefer 
//
void setFramebuffer (int x, int y, float R, float G, float B)
{
	// changes the origin from the lower-left corner to the upper-left corner
	y = ImageH - 1 - y;
	if (R <= 1.0)
		if (R >= 0.0)
			framebuffer[y][x][0] = R;
		else
			framebuffer[y][x][0] = 0.0;
	else
		framebuffer[y][x][0] = 1.0;
	if (G <= 1.0)
		if (G >= 0.0)
			framebuffer[y][x][1] = G;
		else
			framebuffer[y][x][1] = 0.0;
	else
		framebuffer[y][x][1]=1.0;
	if (B <= 1.0)
		if (B >= 0.0)
			framebuffer[y][x][2] = B;
		else
			framebuffer[y][x][2] = 0.0;
	else
		framebuffer[y][x][2] = 1.0;
}


void display( void)
{
	//The next two lines of code are for demonstration only.
	//They show how to draw a line from (0,0) to (100,100)
	int i;
	for(i = 0;i <= 100; i++) setFramebuffer(i,i,1.0,1.0,1.0);

	drawit ();
}


void init (void)
{
	clearFramebuffer ();
}


void mouse (int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
            {
                break;
            }
            break;

        case GLUT_RIGHT_BUTTON:
            break;
    
    }
}


int main(int argc, char** argv)
{
	glutInit (&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize (ImageW,ImageH);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Gustavo Matos - Homework 2");
	init ();	
	glutDisplayFunc (display);
        glutMouseFunc (mouse);
	glutMainLoop ();
	return 0;
}
