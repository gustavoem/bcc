#ifndef ANT_H_
#define ANT_H_

#include <GL/glut.h>
#include <iostream>

class Ant
{

struct Leg {
    float x;
    float z;
    float angle;
};

struct Head {
    float z_rot;
    float x_rot;
};

private:

    // Stores the size of the body
    //
    float body_size;


    // Stores the ant head
    // 
    Head head;

    // Vector of my legs
    //
    Leg * my_legs;

    // Determines the active joint. From 0 to 11 is about legs and 12 is about head
    //
    unsigned int active_joint;


    // Draw ants legs
    //
    void drawLegs ();


    // Draw ants head
    //
    void drawHead ();


    // Draw eye
    //
    void drawEye (float, float, float);

public:

    // Default constructor
    //
    Ant ();


    // Default destructor
    //
    virtual ~Ant ();


    // Draw the ant
    //
    void draw ();


    // Draw Ants leg
    //
    void drawLeg ();


    // Draw 3 axis x,y,z with colors r,g,b
    //
    void drawCoordinates ();


    // Change the member we are interested to move
    //
    void selectNextMember ();


    // Rotates the selected member 
    //
    void rotateMember (int, int);
};

#endif