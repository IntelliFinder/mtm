#include <iostream>

#include "solution.cpp"


using namespace mtm;

int main() {
    Skill skill(45,"bb",10);
    try {
        skill+= -4;

    } catch (NegativePoints& np) {
        std::cout << "Negative points error!" << std::endl;
    }
    return 0;
}

