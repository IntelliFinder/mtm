#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <set>

#include "exceptions.h"
#include "Skill.h"
#include "Citizen.h"

namespace mtm{

    int Citizen::getId() const { return id; }
    std::string Citizen::getFirstName() const {
        return firstName;
    }
    std::string Citizen::getLastName() const {
        return lastName;
    }
    int Citizen::getBirthYear() const {
        return birthYear;
    }

    void Citizen::printShort( std::ostream &str) {
        str<<std::endl; //placeholder
    }
    void Citizen::printLong( std::ostream &str ){
        str<<std::endl; //placeholder
    }
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

   void Citizen::helpForSetInt(int &toChange, const int toAdd){
       toChange += toAdd;
       if (toChange < 0){
           toChange = 0;
       }
   }
}
