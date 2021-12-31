#include <iostream>
#include <string>

#include "skill.h"
#include "citizen.h"

/**==========================SKILL=========================================**/

namespace mtm{
    struct NegativePoints : public std::exception
            //Im not sure that this is the way it's supposed tp be
    {
        const char * what () const throw ()//look! I hope char* is ok even though we shouldnt use it
        {
            return "NegativePoints";
        }
    };

    unsigned int Skill::getId() const { return id; }

    std::string Skill::getName() const { return name; }

    int Skill::requiredPoints() const { return points - pro; }

    Skill& Skill::operator++() {
        points = points + 1;
        return *this;
    }

    Skill& Skill::operator+=(const int amount) {
        if (amount<0)
            throw NegativePoints();
        points = points + amount;
        return *this;
    }
    Skill &Skill::operator+(int amount){
        *this += amount;
        return *this;
    }


    std::ostream &operator<<(std::ostream &os, const Skill &sk) {
        os << sk.getName();
        return os;
    }


    bool operator>(const Skill sk1, const Skill sk2){
        return sk1.getId() > sk2.getId();
    }

    bool operator<(const Skill sk1, const Skill sk2){
        return sk1.getId() < sk2.getId();
    }

    bool operator!=(const Skill sk1, const Skill sk2){
        return sk1.getId() != sk2.getId();
    }

    bool operator>=(const Skill sk1, const Skill sk2){
        return sk1.getId() >= sk2.getId();
    }

    bool operator<=(const Skill sk1, const Skill sk2){
        return sk1.getId() <= sk2.getId();
    }

    bool operator==(const Skill sk1, const Skill sk2){
        return sk1.getId() == sk2.getId();
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
    //Citizen* clone() //look! should we implement it?

    bool operator==(Citizen &c1, Citizen &c2) {
        return c1.getId() == c2.getId();
    }

    bool operator<=(Citizen &c1, Citizen &c2) {
        return c1.getId() <= c2.getId();
    }
    bool operator>=(Citizen &c1, Citizen &c2) {
        return c1.getId() >= c2.getId();
    }

    bool operator!=(Citizen &c1, Citizen &c2) {
        return c1.getId() != c2.getId();
    }

    bool operator<(Citizen &c1, Citizen &c2) {
        return c1.getId() < c2.getId();
    }

    bool operator>(Citizen &c1, Citizen &c2) {
        return c1.getId() > c2.getId();
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
