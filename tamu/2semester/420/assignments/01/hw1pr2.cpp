// Gustavo Estrela de Matos
// CSCE 420-500
// Due: February 1, 2016
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
        unsigned int m;
        unsigned int n;

    public:
        Room (bool ** floor, unsigned int m, unsigned int n)
        {
            this->floor = floor;
            this->n = n;
            this->m = m;
        }
    
        // Number of columns
        unsigned int getRowSize ()
        {
            return n;
        }

        // Number of rows
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
        bool ** visited;
        float score;
        unsigned int clean_tiles;
    
 
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
        // Note that all the actions the vacuum does here are Left, Right, Up and
        // Down as determined in the problem (even tough I did not write the actual 
        // methods for just moving in these directions).
        void updatePosition ()
        {
            //cout << "(" << x << ", " << y <<  ")";            
            
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
            
            //cout << "-> (" << x << ", " << y <<  ")" << endl;            
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
            clean_tiles = 0;

            unsigned int m = room->getColumnSize ();
            unsigned int n = room->getRowSize ();
    
            visited = new bool * [m];
            for (unsigned int i = 0; i < m; i++)
                visited[i] = new bool[n];
            for (unsigned int i = 0; i < m; i++)
                for (unsigned int j = 0; j < n; j++)
                    visited[i][j] = 0;
        }
        
        virtual ~Vacuum ()
        {
            unsigned int m = room->getRowSize ();
            for (unsigned int i = 0; i < m; i++)
                delete[] visited[i];
            delete[] visited;
        }

        void takeAction ()
        {
            if (room->isDirty (x, y))
            {
                room->cleanSquare (x, y);
                clean_tiles++;
                // cout << "Scored at: (" << x << ", " << y << ")" << endl;
            }
            else
            {
                if (!visited[x][y])
                    clean_tiles++;
                updatePosition ();
            }
    
            visited[x][y] = 1;
            score += clean_tiles;
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
    unsigned int rep = 1000;
    double total_score = 0;    
    srand (time(NULL)); 
    room_floor = new bool * [m];
    for (unsigned int i = 0; i < m; i++)
        room_floor[i] = new bool[n];

    for (unsigned int i = 0; i < rep; i++)
    {
        for (unsigned int k = 0; k < m; k++)
            for (unsigned int l = 0; l < n; l++)
                room_floor[k][l] = 0;
        
        unsigned int d = rand () % 1000000;
        for (unsigned int k = 0; k < d; k++)
        {
            unsigned int r = rand () % 1000000;;
            
            // Avoids putting dirt in the same square 
            while (room_floor[r / m][r % n])
                r = (r + 1) % 1000000;

            room_floor[r / m][r % n] = 1; 
        }

        Room room (room_floor, m, n);
        Vacuum vacuum (&room);

        for (unsigned int k = 0; k < 2000000; k++)
            vacuum.takeAction ();
        
        total_score += vacuum.getScore () / 2000.0; // score is over 1000 steps
    }
        

    cout << "Avg score: " << total_score / rep;


    for (unsigned int i = 0; i < m; i++)
        delete[] room_floor[i];
    delete[] room_floor;
    return 0;
}

