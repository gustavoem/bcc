#ifndef ANT_H_
#define ANT_H_

#include <GL/glut.h>


class Ant
{

struct Leg {
    float x;
    float z;
    float angle;
};

private:

    //
    //
    float body_size;


    // Vector of my legs
    //
    Leg * my_legs;

    // Determines the active joint. From 0 to 5 is about legs and 6 is about heada
    //
    unsigned int active_joint;


    // Draw ants legs
    //
    void drawLegs ();


    // Draw ants head
    //
    void drawHead ();

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


    void drawLeg ();


    void drawCoordinates ();
};

#endif