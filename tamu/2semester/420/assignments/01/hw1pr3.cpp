// Gustavo Estrela de Matos
// CSCE 420-500
// Due: February 1, 2016 
// hw1pr3.cpp
//
//
#include <cstdio>
#include <cmath>
#include <vector>
#include <iostream>
#include <list>


double points_distance (std::pair<int, int>  p, std::pair<int, int> q)
{
    double x = p.first - q.first;
    double y = p.second - q.second;
    return sqrt (x * x + y * y);
}

int main ()
{
    std::list <std::pair<int, int> > points;
    std::pair<int, int> last_point;
    std::pair<int, int> first_point;
    int x, y;
    double traveld_distance = 0;
    
    scanf ("%d %d", &x, &y);
    last_point = std::make_pair (x, y);
    first_point = last_point;

    while (scanf ("%d %d", &x, &y) != EOF)
    {
        // std::cout << "Read point (" << x << ", " << y << ") " << std::endl;
        points.push_back (std::make_pair (x, y));
    }
    
    while (!points.empty ())
    {
        std::cout << "Last point: " << last_point.first << ", " << last_point.second << std::endl;
        std::list<std::pair <int, int> >::iterator min_it = points.begin ();
        double min_distance = points_distance (last_point, *min_it);
        for (std::list<std::pair <int, int> >::iterator it = min_it;  it != points.end (); ++it)   
        {
            double d = points_distance (last_point, *it);
            if (d < min_distance)
            {
                min_distance = d;
                min_it = it;
            }
        }
        std::cout << "to " << min_it->first << ", " << min_it->second << ": " << min_distance << std::endl;
        traveld_distance += min_distance;
        last_point = *min_it;
        points.erase (min_it);
    }
    traveld_distance += points_distance (last_point, first_point);
    std::cout << std::endl << traveld_distance << std::endl; 
}

