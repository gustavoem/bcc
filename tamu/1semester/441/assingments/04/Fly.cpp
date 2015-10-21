#include "Fly.h"

Fly::Fly ()
{
	body_size = 1;
}


Fly::~Fly ()
{
	return;
}


void Fly::draw ()
{
	glPushMatrix ();
	// body
	glScalef (1, 0.125, 1.0);
	glutSolidSphere(2, 1000, 1000);
	glPopMatrix ();

}