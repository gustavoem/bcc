#include <iostream>
#include <sstream>

int main() {
    std::ostringstream stm;

    std::cout << "Antes de 'inicializar': " << stm.str() << std::endl;
    stm.str ("");
    stm << "text" << std::endl;
    std::cout << "Depois de 'inicializar': " << stm.str() << std::endl;
    return 0;
}
