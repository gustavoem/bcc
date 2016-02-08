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

        // Returns tile present int this board position
        unsigned int content (unsigned int x, unsigned int y)
        {
            return board[x][y];
        }

        // Comparation operator
        bool operator==(Puzzle8& a)
        {
            for (unsigned int i = 0; i < 9; i++)
                if (a.content (i / 3, i % 3) != this->content (i / 3, i % 3))
                    return false;
            return true;        
        }
};

int main ()
{
    unsigned int ** board;
    unsigned int ** goal_board;

    board = new  unsigned int * [3];
    goal_board = new unsigned int * [3];
    for (unsigned int i = 0; i < 3; i++)
    {
        board[i] = new unsigned int[3];
        goal_board[i] = new unsigned int[3];
    }
    
    for (unsigned int i = 0; i < 9; i++)
    {
        unsigned int x;
        scanf ("%u", &x);
        board[i / 3][i % 3] = x;
    }
    
    for (unsigned int i = 0; i < 9; i++)
    {
        unsigned int x;
        scanf ("%u", &x);
        goal_board[i / 3][i % 3] = x;
    }

    Puzzle8 game ((unsigned int **) board);
    Puzzle8 goal_game ((unsigned int **) goal_board);
    game.printGame ();
    goal_game.printGame ();

    cout << (game == goal_game) << endl;
    
    for (unsigned int i = 0; i < 3; i++)
        delete[] board[i];
    delete[] board;
}


