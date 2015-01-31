#include <iostream>

class Test {
    public:
        Test();
        ~Test();
        void getNo();
};

Test::Test() {
    return;
}

Test::~Test() {
    return;
}

void Test::getNo() {
    std::cout << "Nooooo";
}

int main() {
    Test* teste = new Test();
    teste->getNo();
    return 0;
}
