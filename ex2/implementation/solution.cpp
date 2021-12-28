#include <iostream>

#include "skill.h"
#include "citizen.h"

/**==========================SKILL=========================================**/
namespace mtm{


    unsigned int Skill::getId() const { return id; }

    std::string Skill::getName() const { return name; }

    int Skill::requiredPoints() const { return points; }

    Skill& Skill::operator++() {
        points = points + 1;
        return *this;
    }

    Skill& Skill::operator+=(const int amount) {
        points = points + amount;
        return *this;
    }

}



/**=============================END SKILL=========================================**/

/**===============================CITIZEN=========================================**/
namespace mtm{
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
    void Citizen::printShort( std::ostream str) {
        str<<std::endl; //placeholder
    }
    void Citizen::printLong( std::ostream str ){
        str<<std::endl; //placeholder
    }


}
/**========================END CITIZEN=========================================**/

/**============================MANAGER=========================================**/
/**========================END MANAGER=========================================**/

/**============================CITY=========================================**/
/**========================END CITY=========================================**/

/**============================EMPLOYEE=========================================**/
/**========================END EMPLOYEE=========================================**/

/**============================FACULTY=========================================**/
/**========================END FACULTY=========================================**/
