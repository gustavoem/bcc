#include <iostream>

bool nullbool () {
    return NULL;
}

int main() {
    bool teste;
    teste = nullbool();
    
    if (teste == true || teste == false) 
        std::cout << "teremos problemas" << std::endl;
    else
        std::cout << "nao teremos problemas" << std::endl;
    
    if (teste == true)
        std::cout << "teste e true" << std::endl;
    else
        std::cout << "teste e false" << std::endl; 
    
    return 0;
}
