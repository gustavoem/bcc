#include "Ant.h"

Ant::Ant ()
{
    body_size = 2;
    my_legs = new Leg[12];
    float gap_inter_leg = (float) ((float) 4 * body_size) / 6;
    for (int i = 0; i < 3; i++)
    {
        Leg f_up_leg;
        Leg f_dw_leg;
        Leg b_up_leg;
        Leg b_dw_leg;

        b_up_leg.x = (i - 1) * gap_inter_leg;
        b_up_leg.z = 0.4 + (float) (i % 2) / 10;
        b_up_leg.angle = -90;
        b_dw_leg.angle = 60;
        
        f_up_leg.x = (i - 1) * gap_inter_leg;
        f_up_leg.z = -0.4 - (float) (i % 2) / 10;
        f_up_leg.angle = 90;
        f_dw_leg.angle = 60;
            
        my_legs[2 * i] = b_up_leg;
        my_legs[2 * i + 1] = b_dw_leg;

        my_legs[6 + 2 * i] = f_up_leg;
        my_legs[6 + 2 * i + 1] = f_dw_leg;
    }
}


Ant::~Ant ()
{
    return;
}


void Ant::draw ()
{
    glPushMatrix ();
    
    drawCoordinates ();
    // body
    glColor4f (.4, .2, .2, 1);
    glScalef (1, 0.25, 0.25);
    glutSolidSphere (body_size, 1000, 1000);
    glPopMatrix ();

    // draw legs
    drawLegs ();
}


void Ant::drawLegs ()
{
    for (unsigned int i = 0; i < 6; i++)
    {
        glPushMatrix ();
        // draw junction body-upper leg
        drawCoordinates ();
        glColor4f (0, 0, 0, 0);
        glTranslatef (my_legs[i * 2].x, 0, my_legs[i * 2].z);
        // rotate to make leg
        glRotatef (my_legs[i * 2].angle, 0.0, 1.0, 0); // first with y fixed
        glRotatef (30, 0, 0, 1);                      // then with z fixed
        // now our leg is aligned with x axis we can draw it
        drawLeg ();

        glutSolidSphere (0.1, 100, 100);
        glTranslatef (body_size, 0, 0);
        glColor4f (1,0,0,0);
        glutSolidSphere (0.1, 100, 100);
        drawCoordinates ();
        glPopMatrix ();
    }
}

void Ant::drawLeg ()
{
    glLineWidth (5);
    glBegin (GL_LINES);
    glVertex3f (0, 0, 0);
    glVertex3f (body_size, 0, 0);
    glEnd ();
    glLineWidth (1);    
}


void Ant::drawCoordinates ()
{
    glBegin (GL_LINES);
    glColor4f (1,0,0,1);
    glVertex3f (0, 0, 0);
    glVertex3f (5, 0, 0);
    glColor4f (0,1,0,1);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 5, 0);
    glColor4f (0,0,1,1);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, 5);
    glEnd ();
}