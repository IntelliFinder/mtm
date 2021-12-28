#include <iostream>

#include "skill.h"
#include "citizen.h"

/**==========================SKILL=========================================
operator ++(  );
operator +=( const int amount );
operator +( const int amount );**/
namespace mtm{
/*
    Skill& Skill::operator+=(const int amount) {
        points = points + amount;
        return *this;
    }
    Skill& Skill::operator++(){
        points = points + 1;
        return *this;
    }
*/
    Skill::Skill(const unsigned int id, const std::string name, int points, double pro) : id(id), name(name), points(points), pro(pro) {}

    int Skill::getId() const { return id; }

    std::string Skill::getName() const { return name; }



}



/**==========================END SKILL=========================================**/

/**===========================CITIZEN=========================================**/
namespace mtm{
    Citizen::Citizen(const unsigned int id, const std::string firstName, const std::string lastName, const int birthYear): id(id), firstName(firstName), lastName(lastName), birthYear(birthYear){}
    Citizen::~Citizen(){}
    int Citizen::getId() const { return id; }

}
/**=======================END CITIZEN=========================================**/
