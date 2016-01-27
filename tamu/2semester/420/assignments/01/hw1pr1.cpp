// Gustavo Estrela de Matos
// CSCE 420-500
// Due: February 1, 2016 (or whatever the due date is)
// hw1pr1.cpp
//

#include <cstdio>
#include <iostream>

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
            cout << "(" << x << ", " << y <<  ")";            
            
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
            
            cout << "-> (" << x << ", " << y <<  ")" << endl;            
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
                cout << "Scored at: (" << x << ", " << y << ")" << endl;
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
    unsigned int n, m;
    bool ** room_floor;
    
    scanf ("%u %u", &n, &m);
    room_floor = new bool * [n];
    for (unsigned int i = 0; i < n; i++)
        room_floor[i] = new bool[m];

    cout << "n m: " << (int) n  << " " << (int) m << endl;

    for (unsigned int i = 0; i < n; i++)
        for (unsigned int j = 0; j < m; j++)
        {
            int x;
            scanf ("%d", &x);
            room_floor[i][j] = (bool) x;
        }

    Room room (room_floor, n, m);
    Vacuum vacuum (&room);
    
    for (unsigned int i = 0; i < 2 * m * n; i++)
        vacuum.takeAction ();
    
    cout << "Score: " << vacuum.getScore () << endl;
    for (unsigned int i = 0; i < n; i++)
        delete[] room_floor[i];
    delete[] room_floor;
    return 0;
}

