#include <GL/glut.h>
#include <stdlib.h>
#include "torre.h"
#include "nave.h"
#include "cores.h"

Torre *CriaTorre(double x, double y, double z)
{
  Torre *t = (Torre *)malloc(sizeof(Torre));
  if (t == NULL) return NULL;

  t->px = x;
  t->py = y;
  t->pz = z;
  return t;
}

void DestroiTorre(Torre *t)
{
  free(t);
}

void DesenhaTorre(Torre *t, int deltaz, double rot)
{
  glPushMatrix();
  glTranslatef(t->px, t->py,t->pz-deltaz);

  glRotated(rot, 0, 1, 0);
  glutSolidTeapot(3);

  glPopMatrix();
}
