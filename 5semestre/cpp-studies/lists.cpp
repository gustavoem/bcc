#include <iostream>
#include <list>
#include <stdlib.h>

int main() {
    std::list<int *> ** l = (std::list<int *> **) malloc (10 * sizeof (std::list<int *> *));
    for (unsigned int i = 0; i < 10; i++)
    {
        std::list<int *> * lista = new std::list<int *>();
        l[i] = lista;
    }   
    for (unsigned int i = 0; i < 10; i++)
    {
        std::cout << l[i]->size () << std::endl;
        free(l[i]);
    }
    return 0;
}
