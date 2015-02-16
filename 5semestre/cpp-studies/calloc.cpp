#include <iostream>
#include <stdlib.h>

int main() {
    int * ptr = (int *) calloc (1, sizeof (int));
    std::cout << ptr << " | "<<(ptr == NULL) << std::endl;  
    return 0;
}
