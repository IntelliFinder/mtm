#include <iostream>

#include "skill.h"
#include "citizen.h"

/**==========================SKILL=========================================
operator ++(  );
operator +=( const int amount );
operator +( const int amount );**/
namespace mtm{

    Skill::Skill(const unsigned int id, const std::string name, int points, double pro) : id(id), name(name), points(points), pro(pro) {}

    unsigned int Skill::getId() const { return id; }

    std::string Skill::getName() const { return name; }

    int Skill::requiredPoints() { return points; }

    Skill& Skill::operator++() {
        points = points + 1;
        return *this;
    }

    Skill& Skill::operator+=(const int amount) {
        points = points + amount;
        return *this;
    }

}



/**==========================END SKILL=========================================**/

/**===========================CITIZEN=========================================**/
namespace mtm{
    Citizen::Citizen(const unsigned int id, const std::string firstName, const std::string lastName, const int birthYear): id(id), firstName(firstName), lastName(lastName), birthYear(birthYear){}
    Citizen::~Citizen(){} //not needed
    unsigned int Citizen::getId() const { return id; }
    std::string Citizen::getFirstName(){
        return firstName;
    }
    std::string Citizen::getLastName(){
        return lastName;
    }
    int Citizen::getBirthYear(){
        return birthYear;
    }


}
/**=======================END CITIZEN=========================================**/
