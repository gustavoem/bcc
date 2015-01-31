#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <time.h>

static double vx=0., vy = 0.;
static float r = 0, g = 0, b = 0;
/* Função de desenho (callback) */
void disp(void) {
  GLfloat parms[4] = {0,0,0,1};

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); /* Limpa o desenho e a marcação de profundidade */
  glMatrixMode(GL_MODELVIEW);           /* Coordenadas do modelo */
  glShadeModel(GL_SMOOTH);              /* Suavização */
  glLoadIdentity();                 /* Começa com a matriz identidade (sem transormações */

  /* Posicionamento da câmera */
  gluLookAt(
        0, 0, 0,      /* foco */
        -vx, -vy, -1,     /* posição */
        0, 2, 0);     /* orientação */

  glColor3f(.0,.2,.8);
  glMaterialfv(GL_FRONT_AND_BACK,
         GL_SPECULAR,
         parms
         );

  /*FRONT*/
  glBegin(GL_POLYGON);
  {
  glColor3f(r, 0, b);        glVertex3f(-0.5, -0.5, -0.5); // P1
  glColor3f(0, g, 0);        glVertex3f( -0.5,  0.5, -0.5); // P2
  glColor3f(0,  0, b);        glVertex3f(  0.5,  0.5, -0.5); // P3
  glColor3f(r, 0, 0);        glVertex3f(  0.5, -0.5, -0.5); // P4
  }
  glEnd();

  // Yellow side - BACK
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  1.0, 1.0 );
  glVertex3f(  0.5, -0.5, 0.5 );
  glVertex3f(  0.5,  0.5, 0.5 );
  glVertex3f( -0.5,  0.5, 0.5 );
  glVertex3f( -0.5, -0.5, 0.5 );
  glEnd();
   
  // Purple side - RIGHT
  glBegin(GL_POLYGON);
  glColor3f(  1.0,  0.0,  1.0 );
  glVertex3f( 0.5, -0.5, -0.5 );
  glVertex3f( 0.5,  0.5, -0.5 );
  glVertex3f( 0.5,  0.5,  0.5 );
  glVertex3f( 0.5, -0.5,  0.5 );
  glEnd();
   
  // Green side - LEFT
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -0.5, -0.5,  0.5 );
  glVertex3f( -0.5,  0.5,  0.5 );
  glVertex3f( -0.5,  0.5, -0.5 );
  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();
   
  // Blue side - TOP
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  0.5,  0.5,  0.5 );
  glVertex3f(  0.5,  0.5, -0.5 );
  glVertex3f( -0.5,  0.5, -0.5 );
  glVertex3f( -0.5,  0.5,  0.5 );
  glEnd();
   
  // Red side - BOTTOM
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  0.5, -0.5, -0.5 );
  glVertex3f(  0.5, -0.5,  0.5 );
  glVertex3f( -0.5, -0.5,  0.5 );
  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();

  /* Troca os buffers, para animação suave */
  glutSwapBuffers();

  glFlush();
}

/* Tratamento do mouse */
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

void trocacor(int n) 
{
  printf("%f\n", (float)(rand() % 100) / 100.1);
  r = 1 - (rand() % 100) / 100.1; g = 1 - g / (rand() % 100) / 100.1; b = 1 - b / (rand() % 100) / 100.1; 
  glutTimerFunc(5, trocacor, n);
  glutPostRedisplay();
}

int main(int ac, char *av[])
{
  glutInit(&ac, av);			/* inicialização */
  glutInitWindowSize(800, 600);
  glutInitDisplayMode(GLUT_SINGLE |GLUT_RGBA | GLUT_DEPTH); /* Duplo buffer, Cor e profundidade */
  /*glutInitWindowSize(500,500);*/								/* Tamanho inicial da janela */

  glutCreateWindow("CAIXAAAAAA!");	/* Criação e nome */

  /* Para transparência é necessário misturar as cores do material e do que se encontra atrás */
  /*glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

  /*glEnable(GL_COLOR_MATERIAL);*/	/* Material colorido */
  // glEnable(GL_LIGHTING);		/* Luz */
  // glEnable(GL_LIGHT0);			 Tipo de iluminação 
  // glEnable(GL_DEPTH_TEST);		/* Uso de profundidade */
  glEnable(GL_DEPTH_TEST);
  glClearColor(1,1,1,1);		/* Fundo branco (na verdade limpa a janela com branco) */

  /* Declaração dos callbacks */
  glutDisplayFunc(disp);
  glutTimerFunc(5, trocacor, 1);
  glutMouseFunc(mouse);
  glutMotionFunc(move);


  /* roda o laço principal */
  glutMainLoop();
  return 0;
}
