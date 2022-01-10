#include <iostream>

#include "solution.cpp"


using namespace mtm;
using std::cout;
using std::endl;
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
    Employee e1(1, "John", "Williams", 2002);
    Employee e2(2, "Alex", "Martinez", 2000);
    Manager m1(1,"Robert", "stark", 1980);
    m1.addEmployee(&e1);
    m1.addEmployee(&e2);
    cout << "Short_Print" << endl;
    m1.printShort(cout);
    cout << "Long Print" << endl;
    m1.printLong(cout);
    return 0;

    return 0;
}

