// Gustavo Estrela de Matos
// CSCE 420-500
// Due: February 1, 2016 (or whatever the due date is)
// hw1pr2.cpp
//

#include <cstdio>
#include <iostream>
#include <set>

using namespace std;

class Room 
{
    private:
        bool ** floor;
        unsigned int n;
        unsigned int m;

    public:
        Room (bool ** floor, unsigned int n, unsigned int m)
        {
            this->floor = floor;
            this->n = n;
            this->m = m;
        }

        unsigned int getRowSize ()
        {
            return n;
        }

        unsigned int getColumnSize ()
        {
            return m;
        }

        bool isDirty (unsigned int i, unsigned int j)
        {
            return floor[i][j];
        }

        void cleanSquare (unsigned int i, unsigned int j)
        {
            floor[i][j] = 0;
        }
};


class Vacuum
{
    private:
        unsigned int x;
        unsigned int y;
        unsigned int x_orientation;
        unsigned int vy;
        Room * room;
        float score;
    
 
        // Updates the position of the vacuum
        // The vacuum walks like this:
        // v > v
        // v ^ v 
        // v ^ v   
        // > ^ >...........
        // And when it reaches the end of the room it comes back
        //  .... < v <
        //       ^ v ^
        //       ^ v ^
        //       ^ < ^
        void updatePosition ()
        {
            // cout << "(" << x << ", " << y <<  ")";            
            
            // cases in which you have to come back
            if ((x_orientation == -1 && x == 0 && y == 0) ||
              (x_orientation == 1 && x == room->getColumnSize () - 1 && 
               y == room->getRowSize () - 1)) 
            {
                x_orientation *= -1;
                vy *= -1;
            }

            // cases in which you change column
            if ((y == 0 && vy == -1) || (y == room->getRowSize () -1 && vy == 1))
            {
                x += x_orientation;
                vy *= -1;
            }
            else // regular case
                y += vy;
            
            // cout << "-> (" << x << ", " << y <<  ")" << endl;            
        }

    public:
        Vacuum (Room * room)
        {
            this->room = room;
            x = 0;
            y = 0;
            x_orientation = 1;
            vy = 1;
            score = 0;
        }

        void takeAction ()
        {
            if (room->isDirty (x, y))
            {
                room->cleanSquare (x, y);
                score++;
                // cout << "Scored at: (" << x << ", " << y << ")" << endl;
            }
            else
               updatePosition ();    
        }

        float getScore ()
        {
            return score;
        }
};


int main ()
{
    unsigned int n = 1000, m = 1000;
    bool ** room_floor;
    unsigned int rep = 10;
    double total_score = 0;    
    
    room_floor = new bool * [m];
    for (unsigned int i = 0; i < n; i++)
        room_floor[i] = new bool[m];

    for (unsigned int i = 0; i < rep; i++)
    {
        for (unsigned int k = 0; k < 1000; k++)
            for (unsigned int l = 0; l < 1000; l++)
                room_floor[k][l] = 0;
        
        set<unsigned int> squares;
        for (unsigned int k = 0; k < 1000 * 1000; k++)
            squares.insert (squares.end (), k);
        
        unsigned int n = rand () % 1000;
        for (unsigned int k = 0; k < n; k++)
        {
            unsigned int r = rand () % squares.size ();
            squares.erase (r);
            room_floor[r / 1000][r % 1000] = 1; 
        }

        Room room (room_floor, n, m);
        Vacuum vacuum (&room);

        for (unsigned int k = 0; k < 2000000; k++)
        {
            vacuum.takeAction ();
        }
        
        total_score += vacuum.getScore ();
    }
        

    cout << "Avg score: " << total_score / rep;


    for (unsigned int i = 0; i < n; i++)
        delete[] room_floor[i];
    delete[] room_floor;
    return 0;
}

