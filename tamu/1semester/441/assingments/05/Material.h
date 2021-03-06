/*
    Author: Gustavo Estrela de Matos
    Date: 11/18/15
*/
    
#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "global.h"

class Light
{

private:

    

public:

    // Default constructor
    //
    Light (Vector, Color);


    // Default destructor
    //
    virtual ~Light ();


    // Returns intensity of the light
    //
    Color getIntensity ();
};

#endif