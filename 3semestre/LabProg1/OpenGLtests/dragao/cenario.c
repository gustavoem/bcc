#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include <time.h>
#include "nave.h"
#include "torre.h"
#include "cores.h"


#define NAVE
#define CONE
#define TORRES
#define RIO
#define MARGENS
#define HORIZONTE
void glutBitmapString(void *font, char *s);


static float fog_color[] = {0.8, 0.4, 0.8, .1};
float fogDensity = 0.001;

GLfloat tiltx = 0.;
GLfloat tilty = 0.;
GLfloat tiltz = 0.;

Nave  *nave;
Torre *torre1;
Torre *torre2;

GLfloat giranave = 0;

GLint  tick = 0;

/* chão */
static GLfloat floorVertices[4][3] = {
  {  10.0,  0.0, 1000.0 },		/* SE */
  { -10.0,  0.0, 1000.0 },		/* SD */
  { -10.0,  0.0,  -20.0 },		/* ID */
  {  10.0,  0.0,  -20.0 },		/* IE */
};

/* parede esq */
static GLfloat leftVertices[4][3] = {
  { -10.0,  0.0, 1000.0 },		/* SE */
  { -20.0, 10.0, 1000.0 },		/* SD */
  { -20.0, 10.0,  -20.0 },		/* ID */
  { -10.0,  0.0,  -20.0 },		/* IE */
};

/* parede dir */
static GLfloat rightVertices[4][3] = {
  {  10.0,  0.0,  1000.0 },
  {  20.0, 10.0,  1000.0 },
  {  20.0, 10.0,   -20.0 },
  {  10.0,  0.0,   -20.0 },
};

/* fundo */
#define S  500
#define LL 979
static GLfloat fundoVertices[4][3] = {
  {-S, -S, LL},
  { S, -S, LL},
  { S,  S, LL},
  {-S,  S, LL},
};

static int
loadTexture(char *f)
{
  GLubyte *loc;

  char l[1024];					/* exagerada */
  int  larg,alt,prof;
  FILE *arq = fopen(f, "rb");
  if (arq == NULL) return 0;
  fgets(l,1024,arq);			/* por segurança */
  if (l[0] != 'P' || l[1] != '6') {
	fputs("Sem arquivo", stderr);
	fclose(arq);
	return 0;
  }
  /* pula os comentários */
  int c;
  while ((c = fgetc(arq)) == '#')
		 fgets(l,1024,arq);
  ungetc(c,arq);				/* oops, não era # */

  if (fscanf(arq, "%d %d %d\n", &larg, &alt, &prof) != 3) {
	fputs("Erro no formato\n", stderr);
    fclose(arq);
	return 0;
  }

  /* Setup RGB image for the texture. */
  loc = (GLubyte*) malloc(larg*alt*3);
  if (loc == NULL) {
	fputs("Sem arquivo", stderr);
	fclose(arq);
	return 0;
  }
  fread(loc, sizeof(GLubyte), larg*alt*3, arq);
  fclose(arq);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
  				  GL_LINEAR_MIPMAP_LINEAR);
  
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, larg, alt,
  					GL_RGB, GL_UNSIGNED_BYTE, loc);

  printf("(%d x %d) %d\n",larg, alt,prof);
  return 1;
}

double GiroTorre(Torre* t) 
{
  double desvio;
  double delta = t->pz - .75*tick - nave->pz;

  /* Para diversão: */
  /* glBegin(GL_LINES); */
  /* glVertex3f(t->px, t->py,t->pz-.75*tick); */
  /* glVertex3f(nave->px, nave->py, nave->pz); */
  /* glEnd(); */

  desvio = atan2(delta,  nave->px - t->px);
  desvio *= 180./3.141592654;

  return desvio;
}

int barrel=0;

/* Função de desenho (callback) */
void disp(void) {
  GLfloat sup, inf, dir, esq;

  /* Limpa o desenho e a marcação de profundidade */
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 

  glMatrixMode(GL_MODELVIEW);	/* Coordenadas do modelo */
  glShadeModel(GL_SMOOTH);		/* Suavização */

  glLoadIdentity();	/* Começa com a matriz identidade (sem
					   transormações) */

  /* posição e direção da câmera */
  gluLookAt(
  			0.0,  8.0, -20.0,	/* olho (0,8,60) */
  			0.0,  8.0,   0.0,	/* centro (0,8,0) */
  			0.0,  1.0,   0.0);	/* orientação (topo na direção Y) */

  glColor4f(1.0, 1.0, 1.0,1.0);

  glEnable(GL_NORMALIZE);

  glDisable(GL_TEXTURE_2D);		/* Texturas bi-dimensionais */
  glTexCoord2f(0.,0.);
  /* texto */
  GLfloat PlateColor[]  = {.3f, .0f,1.f, 1.f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, PlateColor);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  PlateColor);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  PlateColor);
  glColor4f(1.0, .85, 0.0,1.0);
  /*glBegin(GL_QUADS);
  {
	glNormal3f( 0.,  -1., -1);
    glVertex3f( 7., 13.,  2.01);
	glNormal3f( 0.,  1., 0);
    glVertex3f( 3., 13.,  2.01);
	glNormal3f( 0.,  1., 1.);
    glVertex3f( 3., 15.,  2.01);
	glNormal3f( 0.,  -1., 0);
    glVertex3f( 7., 15.,  2.01);
  }
  glEnd();*/

  char texto[200];
  sprintf(texto, "Pos. %d", tick);

  glRasterPos2f(6., 14.);
  glColor3f(0.5f,0.0f,0.0f);
  glutBitmapString(GLUT_BITMAP_HELVETICA_18, texto);

  if (barrel) {
	glRasterPos3f(6.5, 13.5,2);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "BARREL ROLL!!!");
  }

#ifdef HORIZONTE
  /* Horizonte */
  glColor4f(1.0, 1.0, 1.0,1.0);

  sup = 1.00;
  inf = 0.27;
  esq = 0.00;
  dir = 1.00;
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  {
    glTexCoord2f(esq, sup);
    glVertex3fv(fundoVertices[0]);

    glTexCoord2f(dir, sup);
    glVertex3fv(fundoVertices[1]);

    glTexCoord2f(dir, inf);
    glVertex3fv(fundoVertices[2]);

    glTexCoord2f(esq, inf);
    glVertex3fv(fundoVertices[3]);
  }
  glEnd();
  glEnable(GL_LIGHTING);
#endif

  glDisable(GL_TEXTURE_2D);		/* Texturas bi-dimensionais */

#ifdef NAVE
  DesenhaNave(nave, giranave, barrel);
#endif

#ifdef TORRES
  Cor(DarkSlateGray,.5);
  DesenhaTorre(torre1, 0.75*tick, GiroTorre(torre1));
  Cor(Teal,0.4);
  DesenhaTorre(torre2, 0.75*tick, GiroTorre(torre2));
  /* gambiarra para manter o número de torres */
  if (torre1->pz < 0.75*tick) torre1->pz = .75*tick + 1000;
  if (torre2->pz < 0.75*tick) torre2->pz = .75*tick + 1000;
#endif

#ifdef CONE
  glColor4f(1.0, 1.0, 1.0,1.0);

  glPushMatrix();
  glTranslatef(  -10., 10., 20.);

  glRotatef(tiltx, 1.,  0.,  0.);
  glRotatef(tilty, 0.,  1.,  0.);
  glRotatef(tiltz, 0.,  0.,  1.);
  GLfloat ConeColor[]  = {1.f, .271f, .0f, 1.f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ConeColor);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  ConeColor);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  ConeColor);
  Laranja;
  glutSolidCone(1., 3., 32.,  4);

  GLfloat ConeColor2[]  = {1.f, .0f, .0f, 1.f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ConeColor2);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  ConeColor2);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  ConeColor2);
  Vermelho;
  glutSolidTorus(.3, .4, 3., 32);

  GLfloat ConeColor3[]  = {.0f, .0f, 1.0f, 1.f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ConeColor3);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  ConeColor3);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  ConeColor3);
  Azul;
  glTranslatef(.0, .5, 1.5);
  glutSolidSphere(.2, 20, 16); 
  glPopMatrix();
#endif

  GLint dd;
  glEnable(GL_TEXTURE_2D);		/* Texturas bi-dimensionais */

#ifdef RIO
  /* Rio */
  dd = 7*tick;
  /* dd = 200; */
  /* dd %= 1024; */
  dd %=200;
  glColor4f(1.0, 1.0, 1.0,1.0);
  glDisable(GL_LIGHTING);
  sup = 4. + dd/1024.;
  inf = 0. + dd/1024.;
  esq = 0.1;
  dir = 200./1024.;				/* 225 */
  glBegin(GL_QUADS);
  {
    glTexCoord2f(sup, esq);
    glVertex3fv(floorVertices[0]);

    glTexCoord2f(sup, dir);
    glVertex3fv(floorVertices[1]);

    glTexCoord2f(inf, dir);
    glVertex3fv(floorVertices[2]);

    glTexCoord2f(inf, esq);
    glVertex3fv(floorVertices[3]);
  }
  glEnd();
#endif

#ifdef MARGENS
  dd  = 3*tick;
  dd %= 1024;

  sup = 4.+dd/1024.;
  inf = 0.+dd/1024.;
  esq = (1024. - 225.)/1024.;
  dir = .95;

  /* Margem esquerda */
  glColor4f(1.0, 1.0, 1.0,1.0);
  glBegin(GL_QUADS);
  {
    glTexCoord2f(sup, esq);
    glVertex3fv(leftVertices[0]);

    glTexCoord2f(sup,dir);
    glVertex3fv(leftVertices[1]);

    glTexCoord2f(inf, dir);
    glVertex3fv(leftVertices[2]);

    glTexCoord2f(inf,esq);
    glVertex3fv(leftVertices[3]);
  }
  glEnd();

  /* Margem direita */
  glBegin(GL_QUADS);
  {
    glTexCoord2f(sup, esq);
    glVertex3fv(rightVertices[0]);

    glTexCoord2f(sup,dir);
    glVertex3fv(rightVertices[1]);

    glTexCoord2f(inf, dir);
    glVertex3fv(rightVertices[2]);

    glTexCoord2f(inf, esq);
    glVertex3fv(rightVertices[3]);
  }
  glEnd();

  glDisable(GL_TEXTURE_2D);		/* Texturas bi-dimensionais */
  glEnable(GL_LIGHTING);
#endif

  /* Troca os buffers, para animação suave */
  glutSwapBuffers();

  glFlush();
}
int pausa = 0;
void tecl(unsigned char k, int x, int y)
{
  switch (k) {
  case 'a': case 'A':
	tiltx += 1;
	break;
  case 'z': case 'Z':
	tiltx -= 1;
	break;
  case 'n': case 'N':
	tilty += 1;
	break;
  case 'm': case 'M':
	tilty -= 1;
	break;
  case 'p': case 'P':
	tiltz += 1;
	break;
  case 'o': case 'O':
	tiltz -= 1;
	break;
  case 'c': case 'C':
	tilty = tiltx = tiltz = .0;
	break;
  case ' ':
	pausa = !pausa;
	break;
  case 'q': case 'Q':
	exit(0);
  }
}

void sptecl(int k, int x, int y)
{
  switch (k) {
  case GLUT_KEY_UP:
	nave->py += .1;
	if (nave->py >= 20.) nave->py = 20.;
	break;
  case GLUT_KEY_DOWN:
	nave->py -= .1;
	if (nave->py <= 0.) nave->py = 0.;
	break;
  case GLUT_KEY_LEFT:
	nave->px += .1;
	if (nave->px+1.5 > 10.+nave->py)
	  nave->px = 10.+nave->py-1.5;
	break;
  case GLUT_KEY_RIGHT:
	nave->px -= .1;
	if (nave->px-1.5 < -10.-nave->py)
	  nave->px = 1.5 -10.-nave->py;
	break;
  case GLUT_KEY_F1:
	giranave += 3.6;
	break;
  case GLUT_KEY_F2:
	giranave -= 3.6;
	break;
  case GLUT_KEY_F3:
	giranave = 0.;
	break;
  case GLUT_KEY_END:
	if (!barrel) barrel = 35.;
	break;
  case GLUT_KEY_PAGE_DOWN:
	if (!barrel) barrel = -35.;
	break;
  }
}

/* Tempo: avança o relógio */
void anda(int n)
{
  if (!pausa) tick++;
  if (barrel < 0) barrel++;
  else if (barrel > 0) barrel --;

  glutTimerFunc(16, anda,1);
  glutPostRedisplay();
}


int main(int ac, char *av[])
{
  /* Inicialização */
  glutInit(&ac, av);

  /* Duplo buffer, cor e profundidade */
  glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGBA | GLUT_DEPTH);

  /* Tamanho inicial da janela */
  glutInitWindowSize(900,900);

  glutCreateWindow("Cenário");	/* Criação e nome */

  glEnable(GL_DEPTH_TEST);		/* Uso de profundidade */
  glEnable(GL_TEXTURE_2D);		/* Texturas bi-dimensionais */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  /* Modo de projeção */
  glMatrixMode(GL_PROJECTION);
  gluPerspective(   40.0,		/* ângulo de visão */
				     1.0,		/* aspecto */
				    20.0,		/* plano próximo */
				  1000.0);		/* plano distante */

  /* coordenadas do modelo */
  glMatrixMode(GL_MODELVIEW);
  /* posição da câmera */
  gluLookAt(0.0, 8.0, 60.0,		/* olho (0,8,60) */
			0.0, 8.0, 0.0,      /* centro(0,8,0) */
			0.0, 1.0, 0.);      /* orientação (topo na direção Y) */


  /* Iluminação: 2 fontes */

  /* Fonte 0, branca pontual */
  GLfloat lightZeroColor[]  = {1.f, .8f, .2f, .9f};
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightZeroColor);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightZeroColor);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);

  GLfloat light_position[]  = {0.f, 80.f, 20.f };
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightZeroColor);

  /* Fonte 1, branca, spot */
  GLfloat lightOneColor[]  = {1.f, 0.0f, 0., .1f};
  glLightfv(GL_LIGHT1, GL_SPECULAR, lightOneColor);
  glLightfv(GL_LIGHT1, GL_AMBIENT,  lightOneColor);
  glLightfv(GL_LIGHT1, GL_DIFFUSE,  lightOneColor);
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 58.0);

  GLfloat light1_position[]  = {-14.5f, 35.f, 0.f };
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  GLfloat spot1_direction[] = { 0.0, 0.0, 1.0 };
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot1_direction);


  glEnable(GL_COLOR_MATERIAL);	/* Material colorido, mesmo com iluminação */
  glEnable(GL_LIGHTING);		/* Luz */
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);

  /* carga das texturas */
  if (loadTexture("texturasn.ppm") == 0)
 	fputs("Não carregou a textura\n", stderr);

  /* Fog */
  glEnable(GL_FOG);
  glFogi(GL_FOG_MODE, GL_EXP);
  glFogf(GL_FOG_DENSITY, fogDensity);
  glFogfv(GL_FOG_COLOR, fog_color);

  glClearColor(1,1,1,1); /* Fundo branco */

  /* Declaração dos callbacks */
  glutDisplayFunc(disp);
  glutTimerFunc(100, anda,1);
  glutKeyboardFunc(tecl);		/* teclas normais */
  glutSpecialFunc(sptecl);		/* teclas especiais */

  /* Objetos móveis */
  nave   = CriaNave(  0.,4.,10.);
  torre1 = CriaTorre( 11, 4, 900.);
  torre2 = CriaTorre(-12, 4, 230.);

  /* roda o laço principal */
  glutMainLoop();
  return 0;
}
