//Gustavo Estrela de Matos
//CSCE 420-500
//Due: February 10, 2016
//hw2pr2.cpp

#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>

using namespace std;

static string moves[4] = {"UP", "RIGHT", "DOWN", "LEFT"};

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

        
        // Default destructor
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


        pair <int, int> findTile (unsigned int tile)
        {
            for (unsigned int i = 0; i < 3; i++)
                for (unsigned int j = 0; j < 3; j++)
                    if (board[i][j] == tile)
                        return make_pair (i, j);
            return make_pair (-1, -1);
        }


        unsigned int manhattanDistance (Puzzle8& goal)
        {
            unsigned int distance = 0;
            for (unsigned int i = 0; i < 3; i++)
                for (unsigned int j = 0; j < 3; j++)
                {
                    pair<int, int> goal_position = goal.findTile (board[i][j]);
                    distance += abs (i - goal_position.first) + abs (j - goal_position.second);
                }
            return distance;
        }
};


// Represents a node in the search
struct Node
{
    Node * prev;            // Last game state
    unsigned int last_move; // Move between the previous and current state
    Puzzle8 * state;        // Current game state 
    unsigned int depth;     // Depth of the node

    // Stores function values for A* algorithm
    unsigned int current_cost;     // g(x)
    unsigned int heuristic_cost;   // h(x)
};


struct NodeComparison
{
    bool operator ()(const Node * a, const Node * b) const
    {
        return a->current_cost + a->heuristic_cost < b->current_cost + b->heuristic_cost;
    }
};


// Perfors the A* search
Node * AStar (Puzzle8 game, Puzzle8 goal, vector<Node *> * expanded_nodes)
{
    priority_queue<Node *, vector<Node *>, NodeComparison> pq;
    Node * first = new Node;
    expanded_nodes->push_back (first);
    pq.push (first);
    first->prev = NULL;
    first->state = new Puzzle8 (game);
    first->depth = 0;
    first->current_cost = 0;
    first->heuristic_cost = first->state->manhattanDistance (goal);

    while (!pq.empty ())
    {
        Node * current = pq.top ();
        pq.pop ();

        if (*(current->state) == goal)
            return current;
        
        else if (current->depth < 10)
            for (unsigned int i = 0; i < 4; i++)
                if (current->state->isValidMove (i))
                {
                    Node * child = new Node;
                    child->prev = current;
                    child->last_move = i;
                    Puzzle8 * child_state = new Puzzle8 (*(current->state));
                    child_state->moveBlank (i);
                    child->state = child_state;
                    child->depth = current->depth + 1;
                    child->current_cost = current->current_cost + 1;
                    child->heuristic_cost = child_state->manhattanDistance (goal);
                    
                    expanded_nodes->push_back (child);
                    pq.push (child);
                }
                       
    }
    return NULL;
}


// Using a BFS with max depth of 10 searches for a game solution
// and prints it into the screen
void print_solution (Puzzle8 game, Puzzle8 goal)
{
    vector<Node *> expanded_nodes;
    
    Node * solution_node = AStar (game, goal, &expanded_nodes);
    
    if (solution_node == NULL)
        cout << "Could not find a solution" << endl;
    else
    {
        stack<Node *> path;
        Node * current = solution_node;
        while (current != NULL)
        {
            path.push (current);
            current = current->prev;
        }
        
        cout << "Start" << endl;
        current = path.top ();
        path.pop ();
        current->state->printGame ();
        while (!path.empty ())
        {
            cout << moves[path.top ()->last_move] << endl;
            current = path.top ();
            path.pop ();
            current->state->printGame ();
        }
    }
    cout << "Generated " << expanded_nodes.size () << " nodes in total." << endl;

    while (!expanded_nodes.empty ())
    {
        delete expanded_nodes.back ()->state;
        delete expanded_nodes.back ();
        expanded_nodes.pop_back ();
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

    print_solution (game, goal_game);

    for (unsigned int i = 0; i < 3; i++)
    {
        delete[] board[i];
        delete[] goal_board[i];
    }
    delete[] goal_board;
    delete[] board;
}
