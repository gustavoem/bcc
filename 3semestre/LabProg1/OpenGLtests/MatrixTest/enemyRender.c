#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <time.h>

static double vx=0., vy = 0.;
static float enemyZ=.5, enemyY=.5, enemyX=.5, shipZ = 0;

void enemyRender() {
    GLfloat parms[4] = {0,0,0,1};

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); /* Limpa o desenho e a marcação de profundidade */
    glShadeModel(GL_SMOOTH);              /* Suavização */

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (GLfloat)800 / (GLfloat)600, 1.0, 500.0);

    printf("%f ", shipZ);

    //gluLookAt(
      //  0, 0, 0,      /* foco */
        //-vx, -vy, -1,     /* posição */
        //0, 2, 0);     /* orientação */

    
    glMaterialfv(GL_FRONT_AND_BACK,
         GL_SPECULAR,
         parms
         );

    glLineWidth(2.5); 
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(-.5, 0, 0);
    glEnd();

    glPushMatrix();

    

    glTranslatef(0, 0, 0.4);
    glColor3f(shipZ,.0,.0);
    glBegin( GL_LINE_LOOP );/// don't workglPointSize( 0.0 );
    GLUquadricObj *quadric;
    quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL );
    gluSphere( quadric , 1.5 , 36, 18);
    gluDeleteQuadric(quadric); 
    glEndList();
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
    glFlush();
}

void trocacor(int n) 
{
    printf("entrei!\n");
    shipZ += 0.001;
    glutTimerFunc(10, trocacor, n);
    glutPostRedisplay();
}

void mouse(int b, int s, int x, int y)
{
  if (b == GLUT_RIGHT_BUTTON) { /* reposiciona a câmera */
  vx = vy = 0;
  return;
  }
  if (b == GLUT_MIDDLE_BUTTON) { /* descola a visão */
  vx = x/500.-1.;
  vy = y/500.-1.;
  }
}

/* Movimentação: reposiciona a câmera */
void move(int x, int y)
{
  vx = x/250.-1.;
  vy = y/250.-1.;

  glutPostRedisplay();      /* força o redesenho */
}

int main(int ac, char *av[]) {
    glutInit(&ac, av);          /* inicialização */
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_SINGLE |GLUT_RGBA | GLUT_DEPTH); /* Duplo buffer, Cor e profundidade */
    glutCreateWindow("CAIXAAAAAA!");
    glEnable(GL_DEPTH_TEST);
    glClearColor(1,1,1,1);

    glutDisplayFunc(enemyRender);
    glutTimerFunc(10, trocacor, 1);
    glutMouseFunc(mouse);
    glutMotionFunc(move);

    glutMainLoop();
    return 0;
}