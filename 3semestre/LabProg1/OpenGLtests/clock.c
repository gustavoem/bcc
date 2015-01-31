#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 4*atan(1.)

/* Algumas variáveis globais, veja a discussão em aula */
static double seg,min,hr;		/* Marcação da hora corrente */
static double vx=0., vy = 0.;	/* Posição da câmera */

/* Função de desenho (callback) */
void disp(void) {
  int i;
  GLfloat parms[4] = {0,0,0,1};

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); /* Limpa o desenho e a marcação de profundidade */
  glMatrixMode(GL_MODELVIEW);						/* Coordenadas do modelo */
  glShadeModel(GL_SMOOTH);							/* Suavização */
  glLoadIdentity();									/* Começa com a matriz identidade (sem transormações */

  /* Posicionamento da câmera */
  gluLookAt(
  			0, 0, 0,			/* foco */
  			-vx,-vy,-1,			/* posição */
  			0, 2, 0);			/* orientação */

  /* Definição das características do material */
    glMaterialfv(GL_FRONT_AND_BACK,
			   GL_SPECULAR,
			   parms
			   );

  /* Anel externo - borda */
  glColor3f(.0,.2,.8);
  glBegin(GL_QUAD_STRIP);
  {
	double x,y;

	for(i=0; i<=360;i+=2) {
	  x=cos(2*i*PI/360.);
	  y=sin(2*i*PI/360.);
	  glColor3f(0,(1.+x)/3.,(1.+y)/3.);
	  glVertex3f(.8*x,.8*y,0);
	  glVertex3f(.95*x,.95*y,.05);
	}
  }
  glEnd();

  /* Anel externo */
  glBegin(GL_QUAD_STRIP);
  {
	double x,y;

	for(i=0; i<=360;i+=2) {
	  x=cos(2*i*PI/360.);
	  y=sin(2*i*PI/360.);
	  glColor3f(0,(1.+x)/2.,(1.+y)/2.);
	  glVertex3f(.95*x,.95*y,.05);
	  glVertex3f(x,y,0);
	}
  }
  glEnd();
 
  /* Marcas das horas */
  glColor3f(.0,.0,.0);
  glPushMatrix();
  for(i=0; i<=360;i+=30) {
	glRotatef(-30, 0,0,1);		/* gira o sistema de coordenadas, facilitando o desenho */
	glBegin(GL_QUADS); {
	  glVertex3f(-0.025,  0.7, -0.02);
	  glVertex3f(-0.025,  0.8, -0.02);
	  glVertex3f( 0.025,  0.8, -0.02);
	  glVertex3f( 0.025,  0.7, -0.02);
	} 
	glEnd();
  }
  glPopMatrix();

  /* Ponteiro das horas */
  glColor3f(.9,.3,0);
  glPushMatrix();
  glRotatef(-hr, 0,0,1);
  glBegin(GL_QUADS); 
  {
	glVertex3f(-0.05,  0.00, -0.03);
	glVertex3f( 0.00, -0.05, -0.03);
	glVertex3f( 0.05,  0.00, -0.03);
	glVertex3f( 0.00,  0.50, -0.03);
  }
  glEnd();
  glPopMatrix();

  /* Ponteiro dos minutos */
  glColor3f(.7,.5,.2);
  glPushMatrix();
  glRotatef(-min, 0,0,1);
  glBegin(GL_QUADS); 
  {
	glVertex3f(-0.03,  0.00, -0.04);
	glVertex3f( 0.00, -0.05, -0.04);
	glVertex3f( 0.03,  0.00, -0.04);
	glVertex3f( 0.00,  0.80, -0.04);
  }
  glEnd();
  glPopMatrix();

  /* Ponteiro dos segundos */
  parms[0] = parms[1] = parms[2] = .8;
  glMaterialfv(GL_FRONT_AND_BACK,
  			   GL_EMISSION,
  			   parms
  			   );
  glColor3f(.7,.1,.1);
  glPushMatrix();
  glRotatef(-seg, 0,0,1);
  glBegin(GL_QUADS); 
  {
	glVertex3f(-0.01,  0.00, -0.042);
	glVertex3f( 0.00, -0.01, -0.042);
	glVertex3f( 0.01,  0.00, -0.042);
	glVertex3f( 0.00,  0.80, -0.042);
  }
  glEnd();
  glPopMatrix();

  /* Novo material */
  parms[0] = parms[1] = parms[2] = 0;
  glMaterialfv(GL_FRONT_AND_BACK,
  			   GL_EMISSION,
  			   parms
  			   );
  
  /* Fundo do mostrador */

  glColor3f(.2,.2,.0);
  glBegin(GL_TRIANGLE_FAN);
  {
	double x,y;

	glVertex3f(0.,0.,0.);
	for(i=0; i<=360;i+=2) {
	  x=cos(2*i*PI/360.);
	  y=sin(2*i*PI/360.);
	  glVertex3f(.8*x,.8*y,0.);
	}
  }
  glEnd();

  /* Tampa */
  parms[0] = parms[1] = parms[2] = .5;
  glMaterialfv(GL_FRONT_AND_BACK,
			   GL_SPECULAR,
			   parms
			   );
  glColor4f(0,0,1,.15);
  glBegin(GL_TRIANGLE_FAN);
  {
	double x,y;

	glVertex3f(0.,0.,-0.05);

	for(i=0; i<=360;i+=2) {
	  x=cos(2*i*PI/360.);
	  y=sin(2*i*PI/360.);
	  glVertex3f(.8*x,.8*y,-0.05);
	}
  }
  glEnd();

  /* Troca os buffers, para animação suave */
  glutSwapBuffers();

  glFlush();
}

/* Qualquer tecla termina o programa */
void tecl(unsigned char k, int x, int y)
{
  exit(0);
}

/* Tratamento do mouse */
void mouse(int b, int s, int x, int y)
{
  if (b == GLUT_RIGHT_BUTTON) {	/* reposiciona a câmera */
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

  glutPostRedisplay();			/* força o redesenho */
}

/* Tempo: avança o relógio */
void anda(int n)
{
  struct tm *t;
  time_t rt = time(NULL);
  /* pega o tempo e transforma em ângulos */
  t = localtime(&rt);
  seg = t->tm_sec;
  min = t->tm_min+ seg/60.;
  hr  = t->tm_hour+min/60.;
  seg *= 6;						/* 60s = 360° */
  min *= 6;						/* 60m = 360° */
  hr  *= 30;					/* 12h = 360° */

  glutTimerFunc(1000, anda, n);
  glutPostRedisplay();
}


int main(int ac, char *av[])
{
  glutInit(&ac, av);			/* inicialização */
  glutInitWindowSize(800, 600);
  glutInitDisplayMode(GLUT_SINGLE |GLUT_RGBA | GLUT_DEPTH); /* Duplo buffer, Cor e profundidade */
  /*glutInitWindowSize(500,500);*/								/* Tamanho inicial da janela */

  glutCreateWindow("Relógio");	/* Criação e nome */

  /* Para transparência é necessário misturar as cores do material e do que se encontra atrás */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_COLOR_MATERIAL);	/* Material colorido */
  glEnable(GL_LIGHTING);		/* Luz */
  glEnable(GL_LIGHT0);			/* Tipo de iluminação */
  glEnable(GL_DEPTH_TEST);		/* Uso de profundidade */

  glClearColor(1,1,1,1);		/* Fundo branco (na verdade limpa a janela com branco) */

  /* Declaração dos callbacks */
  glutDisplayFunc(disp);
  glutTimerFunc(10, anda, 1);
  glutKeyboardFunc(tecl);
  glutMouseFunc(mouse);
  glutMotionFunc(move);

  /* inicialização das variáveis */
  // seg = 0; min = 90; hr=180;

  /* roda o laço principal */
  glutMainLoop();
  return 0;
}
