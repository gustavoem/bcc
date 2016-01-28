#include <cstdio>
#include <cmath>
#include <vector>
#include <iostream>
#include <list>


using namespace std;


double distance (pair<int, int>  p, pair<int, int> q)
{
    int x;
    int y;
    x = p.first - q.first;
    y = p.second - q.second;
    return sqrt (x * x + y * y);
}

int main ()
{
    list <pair<int, int> > points;
    pair<int, int> last_point;
    pair<int, int> first_point;
    int x, y;
    double traveld_distance = 0;
    
    scanf ("%d %d", &x, &y);
    last_point = make_pair (x, y);
    first_point = last_point;

    while (scanf ("%d %d", &x, &y) != EOF)
    {
        //cout << "Read point (" << x << ", " << y << ") " << endl;
        points.push_back (make_pair (x, y));
    }
    
    while (!points.empty ())
    {
        // cout << "Last point: " << last_point.first << ", " << last_point.second << endl;
        list<pair <int, int>>::iterator min_it = points.begin ();
        double min_distance = distance (last_point, *min_it);
        for (list<pair <int, int>>::iterator it = min_it;  it != points.end (); ++it)   
        {
            double d = distance (last_point, *it);
            if (d < min_distance)
            {
                min_distance = d;
                min_it = it;
            }
        }
        // cout << "to " << min_it->first << ", " << min_it->second << ": " << min_distance << endl;
        traveld_distance += min_distance;
        last_point = *min_it;
        points.erase (min_it);
    }
    traveld_distance += distance (last_point, first_point);
    cout << endl << traveld_distance << endl; 
}

