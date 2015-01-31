#include <GL/glut.h>
#include <stdlib.h>
#include "nave.h"
#include "cores.h"

Nave *CriaNave(double x, double y, double z)
{
  Nave *n = (Nave *)malloc(sizeof(Nave));
  if (n == NULL) return NULL;

  n->px = x;
  n->py = y;
  n->pz = z;
  return n;
}

void DestroiNave(Nave *n)
{
  free(n);
}

void DesenhaNave(Nave *n, GLfloat ang, GLint barrel)
{
  glPushMatrix();
  glTranslatef(n->px, n->py,n->pz);
  /* glRotatef(-90, 0, 1, 0); */
  glRotatef(-90, 1, 0, 0);
  glRotatef(-90, 0, 0, 1);
  glRotatef(ang, 0, 0, 1);

  glRotatef(barrel*30, 1, 0, 0);

  glScalef(.1,.1,.1);
  Vermelho;
#include "GLnave.inc"
  glPopMatrix();
}
