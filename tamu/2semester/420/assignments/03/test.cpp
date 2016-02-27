#include <map>
#include <iostream>

using namespace std;

int main ()
{
    map<char, int> mapa;
    
    cout << mapa.size () << endl;
    cout << mapa['t'] << endl;
    cout << mapa.size () << endl;
}
