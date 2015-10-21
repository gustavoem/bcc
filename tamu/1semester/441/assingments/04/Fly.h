#ifndef FLY_H_
#define FLY_H_

#include <GL/glut.h>


class Fly
{

private:

    float body_size;


public:

    // Default constructor
    //
    Fly ();


    // Default destructor
    //
    virtual ~Fly ();


    void draw ();

};

#endif