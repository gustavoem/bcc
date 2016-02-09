//Gustavo Estrela de Matos
//CSCE 420-500
//Due: February 10, 2016
//hw2pr1.cpp

#include <cstdio>
#include <iostream>
#include <vector>


using namespace std;

class Puzzle8
{
    private:

        // Stores the board configuration
        unsigned int  ** board;
        unsigned int blank_x;
        unsigned int blank_y;
    
        
        // Allocs memory for the board
        void init_board () 
        {
            board = new  unsigned int * [3];
            for (unsigned int i = 0; i < 3; i++)
                board[i] = new unsigned int[3];
        }


        // Copies a board to be the instance's board
        void copy_board (unsigned int ** board)
        {
            for (unsigned int i = 0; i < 3; i++)
                for (unsigned int j = 0; j < 3; j++)
                {
                   this->board[i][j] = board[i][j];
                   if (board[i][j] == 0)
                   {
                       blank_x = j;
                       blank_y = i;
                   }
                }
        }

    public:
        
        // Default constructor
        Puzzle8 (unsigned int ** board)
        {
            init_board ();
            copy_board (board);
        }


        ~Puzzle8 ()
        {
            for (unsigned int i = 0; i < 3; i++)
                delete[] board[i];
            delete[] board;
        }


        // Copy constructor
        Puzzle8 (Puzzle8 &original)
        {
            init_board ();
            copy_board (original.getBoard ());
        }

        
        // Returns the game board
        unsigned int ** getBoard ()
        {
            return board;
        }


        // Move the blank tile
        // 0 for UP
        // 1 for RIGHT
        // 2 for DOWN
        // 3 for LEFT
        // Returns false if move is not possible
        bool moveBlank (unsigned int move)
        {
            if (!isValidMove (move))   
                return false;
            
            switch (move)
            {
                case 0:
                    board[blank_y][blank_x] = board[blank_y - 1][blank_x];
                    blank_y--;
                    break;

                case 1:
                    board[blank_y][blank_x] = board[blank_y][blank_x + 1];
                    blank_x++;
                    break;

                case 2:
                    board[blank_y][blank_x] = board[blank_y + 1][blank_x];
                    blank_y++;
                    break;

                case 3:
                    board[blank_y][blank_x] = board[blank_y][blank_x -1];
                    blank_x--;
                    break;
            }

            board[blank_y][blank_x] = 0;
            return true;
        }


        // Verify if move is valid
        bool isValidMove (unsigned int move)
        {
            if (blank_y == 0 && move == 0)
                return false;
            
            if (blank_x == 2 && move == 1)
                return false;

            if (blank_y == 2 && move == 2)
                return false;

            if (blank_x == 0 && move == 3)
                return false;

            return true;
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


// Represents a node in the search
struct Node
{
    Node * prev; // the last game state
    unsigned int last_move; // the move between the previous and current state
    Puzzle8 * state; // the current game state 
};


// Using a BFS with max depth of 10 searches for a game solution
// and prints it into the screen
void print_solution (Puzzle8 game, Puzzle8 goal)
{
    Node * current = new Node;
    current->prev = NULL;
    current->state = &game;
    
    for (unsigned int i = 0; i < 4; i++)
    {
        Puzzle8 * child_state = new Puzzle8 (*current->state);
        child_state->moveBlank (i);
        cout << "Child " << i << ": " << endl;
        child_state->printGame ();
        cout << endl;
        delete child_state;
    }
}

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

    cout << "Original: " << endl;
    game.printGame ();    

    print_solution (game, goal_game);

    for (unsigned int i = 0; i < 3; i++)
    {
        delete[] board[i];
        delete[] goal_board[i];
    }
    delete[] goal_board;
    delete[] board;
}
