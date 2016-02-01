#include <cstdio>
#include <cmath>
#include <vector>
#include <iostream>
#include <list>


using namespace std;

struct Node {
    pair <int, int> p;
    Node * previous;
    
};

double distance (pair<int, int>  p, pair<int, int> q)
{
    int x;
    int y;
    x = p.first - q.first;
    y = p.second - q.second;
    return sqrt (x * x + y * y);
}


double shortest_closed_path (list<pair<int, int> > * points)
{
    
}

int main ()
{
    list <pair<int, int> > points;
    pair<int, int> last_point;
    pair<int, int> first_point;
    int x, y;
    double traveld_distance = 0;
    Node * bfs_root;
    
    scanf ("%d %d", &x, &y);
    last_point = make_pair (x, y);
    first_point = last_point;

    while (scanf ("%d %d", &x, &y) != EOF)
    {
        //cout << "Read point (" << x << ", " << y << ") " << endl;
        points.push_back (make_pair (x, y));
    }
    
    traveld_distance = distance shortest_closed_path (&points);
    cout << endl << traveld_distance << endl; 
}
