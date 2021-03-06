#include "Ant.h"

using namespace std;

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
        b_up_leg.direc = 1;
        b_dw_leg.angle = 90;
        b_dw_leg.direc = 1;
        
        f_up_leg.x = (i - 1) * gap_inter_leg;
        f_up_leg.z = -0.4 - (float) (i % 2) / 10;
        f_up_leg.angle = 90;
        f_up_leg.direc = 1;
        f_dw_leg.angle = 90;
        f_dw_leg.direc = 1;
            
        my_legs[2 * i] = b_up_leg;
        my_legs[2 * i + 1] = b_dw_leg;

        my_legs[6 + 2 * i] = f_up_leg;
        my_legs[6 + 2 * i + 1] = f_dw_leg;
    }

    head.z_rot = 0;
    head.x_rot = 0;
    active_joint = 0;

    my_legs[0].angle -= 30;
    my_legs[6].angle -= 30;

    my_legs[4].angle += 30;
    my_legs[10].angle += 30;
}


Ant::~Ant ()
{
    return;
}


void Ant::draw ()
{
    // body
    glPushMatrix ();
    glColor4f (.4, .2, .2, 1);
    glScalef (1, 0.25, 0.25);
    glutSolidSphere (body_size, 1000, 1000);
    glPopMatrix ();

    // draw legs
    drawLegs ();

    // draw head
    drawHead ();
}


void Ant::drawLegs ()
{
    for (unsigned int i = 0; i < 6; i++)
    {
        glPushMatrix ();
        
        // draw junction body-upper leg
        glTranslatef (my_legs[i * 2].x, 0, my_legs[i * 2].z);
        glColor4f (.4, .3, .3, 1);
        if (2 * i == active_joint)
            glColor4f (1, .2, .2, 1);
        glutSolidSphere (0.1, 100, 100);
        
        // rotate to make leg
        glRotatef (my_legs[i * 2].angle, 0.0, 1.0, 0); // first with y fixed
        glRotatef (30, 0, 0, 1);                      // then with z fixed
        // now our leg is aligned with x axis we can draw it
        drawLeg ();

        // draw juntcion upper leg - lower leg
        glTranslatef (body_size, 0, 0);
        glColor4f (.4, .3, .3, 1);
        if (2 * i + 1 == active_joint)
            glColor4f (1, .2, .2, 1);
        glutSolidSphere (0.1, 100, 100);
        glRotatef (-my_legs[i * 2 + 1].angle, 0, 0, 1);
        glPushMatrix ();
        glScalef (1, 0.5, 0.5); // make lower leg bigger
        drawLeg ();
        glPopMatrix ();

        glPopMatrix ();
    }
}

void Ant::drawLeg ()
{
    glLineWidth (5);
    glColor4f (.2, .1, .1, 1);
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

void Ant::drawHead ()
{
    glPushMatrix ();
    glTranslatef (2, 0, 0);

    glRotatef (head.z_rot, 0, 0, 1);
    glRotatef (head.x_rot, 1, 0, 0);

    glColor4f (.4, .3, .3, 1);
    if (12 == active_joint)
            glColor4f (1, .2, .2, 1);
    glutSolidSphere (0.1, 100, 100);
    glTranslatef (body_size / 8, body_size / 8, 0);

    glPushMatrix ();
    glScalef (1, 0.5, 1);
    glColor4f (.4, .2, .2, 1);
    glutSolidSphere (body_size / 4, 100, 100);
    glPopMatrix ();

    // ants antenna
    glLineWidth (5);
    glBegin (GL_LINES);
    glVertex3f (0, 0, 0);
    glVertex3f (body_size / 2, body_size / 2, + 0.2);
    glVertex3f (0, 0, 0);
    glVertex3f (body_size / 2, body_size / 2, - 0.2);
    glEnd ();
    glLineWidth (1);

    // and the eyes
    drawEye (body_size / 4, 0.1, 0.1);
    drawEye (body_size / 4, 0.1, -0.1);

    // and mouthe
    glLineWidth (5);
    glBegin (GL_LINES);
        glVertex3f (body_size / 4 -0.025, -0.1, 0.2);
        glVertex3f (body_size / 4 -0.025, -0.1, -0.2);
    glEnd ();

    glPopMatrix ();
}


void Ant::drawEye (float x, float y, float z)
{
    glPushMatrix ();
    glTranslatef (x, y, z);
    glScalef (0.2, 1, 0.5);
    glColor4f (1,1,1,1);
    glutSolidSphere (.1, 100, 100);
    glColor4f (0,0,0,1);
    glTranslatef (0.1, 0, 0);
    glutSolidSphere (.05, 100, 100);
    glPopMatrix ();
}


void Ant::selectNextMember ()
{
    active_joint += 1;
    active_joint %= 13;
}


void Ant::rotateMember (int ax1_clock, int ax2_clock)
{
    if (active_joint != 12) // its a leg
    {
        float angle = my_legs[active_joint].angle;
        float abs_next_angle = angle + ax1_clock;
        if (angle < 0)
            abs_next_angle *= -1;
        if (abs_next_angle < 121 && abs_next_angle > 59)
            angle += ax1_clock;
        my_legs[active_joint].angle = angle;
    }
    else
    {
        if (head.z_rot + ax1_clock < 30 && head.z_rot + ax1_clock > 0)
            head.z_rot += ax1_clock;
        if (head.x_rot + ax2_clock < 30 && head.x_rot + ax2_clock > -30)
            head.x_rot += ax2_clock;
    }
}


void Ant::walkStep ()
{
    // upper legs
    for (unsigned int i = 0; i < 3; i++)
    {
        // back legs
        my_legs[2 * i].angle += (float) my_legs[2 * i].direc * 4;
        if (my_legs[2 * i].angle > -60)
            my_legs[2 * i].direc = -1;
        if (my_legs[2 * i].angle < -120)
            my_legs[2 * i].direc = 1;

        // front legs
        my_legs[6 + 2 * i].angle += (float) my_legs[6 + 2 * i].direc * 4;
        if (my_legs[6 + 2 * i].angle < 60)
            my_legs[6 + 2 * i].direc = 1;
        if (my_legs[6 + 2 * i].angle > 120)
            my_legs[6 + 2 * i].direc = -1;
    }

    // lower legs goes up when the upper has an angle near 90
    for (unsigned int i = 0; i < 3; i++)
    {
        float upper_angle = my_legs[2 * i].angle;
        if (upper_angle < 0)
            upper_angle *= (-1);
        // used polynomial regression for this
        float angle = ((my_legs[2 * i].direc - 1) / -2) *
         (-3.333333333e-2 * upper_angle * upper_angle + 6 * upper_angle - 240);
        my_legs[2 * i + 1].angle = angle + 90;
    }
    for (unsigned int i = 3; i < 6; i++)
    {
        float upper_angle = my_legs[2 * i].angle;
        if (upper_angle < 0)
            upper_angle *= (-1);
        // used polynomial regression for this
        float angle = ((my_legs[2 * i].direc + 1) / 2) *
         (-3.333333333e-2 * upper_angle * upper_angle + 6 * upper_angle - 240);
        my_legs[2 * i + 1].angle = angle + 90;
    }

}