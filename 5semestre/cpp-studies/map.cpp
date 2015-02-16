#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>

void teste (std::map<char, int> * mapa)
{
    (*mapa)['c'] = 21212;
    return;
}
int main ()
{
    std::map<char, int> mymap;
    int lala = 20;
    //mymap['a'] = lala;
    teste (&mymap);
    std::cout << mymap['c'] << std::endl;
    return 0;
}
