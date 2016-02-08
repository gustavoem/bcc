//Gustavo Estrela de Matos
//CSCE 420-500
//Due: February 10, 2016
//hw2pr1.cpp

#include <cstdio>
#include <iostream>


using namespace std;

class Puzzle8
{
    private:

        // Stores the board configuration
        unsigned int  ** board;
    
    public:
        
        // Default constructor
        Puzzle8 (unsigned int ** board)
        {
            this->board = board;
        }

        // Move the blank tile
        // 0 for UP
        // 1 for RIGHT
        // 2 for DOWN
        // 3 for LEFT
        void moveBlank (unsigned int move)
        {
            return;
        }


        // Verify if move is valid
        bool isValidMove (unsigned int move)
        {
            return false;
        }
    

        // Prints the game in the stdout
        void printGame ()
        {
            for (unsigned int i = 0; i < 3; i++)
            {
                for (unsigned int j = 0; j < 3; j++)
                {
                    cout << board[i][j] << " ";
                }
                cout << endl;
            }
        }
};

int main ()
{
    unsigned int ** board;

    board = new  unsigned int * [3];
    for (unsigned int i = 0; i < 3; i++)
        board[i] = new unsigned int[3];
    
    for (unsigned int i = 0; i < 9; i++)
    {
        unsigned int x;
        scanf ("%u", &x);
        board[i / 3][i % 3] = x;
    }

    Puzzle8 game ((unsigned int **) board);
    game.printGame ();
    
    for (unsigned int i = 0; i < 3; i++)
        delete[] board[i];
    delete[] board;
}


