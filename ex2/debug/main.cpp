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
    Employee emp(1,"Shai","Gol",2004);
    emp.setScore(9);
    try {
        emp.learnSkill(skill);
    }
    catch (CanNotLearnSkill& c){
        std::cout << "cant learn skill is ok" << std::endl;
    }
    emp.setScore(2);
    emp.learnSkill(skill);
    emp.printShort(std::cout);
    emp.printLong(std::cout);
    return 0;
}

