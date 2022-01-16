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

    void Citizen::printShort( std::ostream &stream) {
        stream << std::endl; //placeholder
    }
    void Citizen::printLong( std::ostream &stream ){
        stream << std::endl; //placeholder
    }
   bool operator==(Citizen &citizen_1, Citizen &citizen_2) {
       return citizen_1.getId() == citizen_2.getId();
   }

   bool operator<=(Citizen &citizen_1, Citizen &citizen_2) {
       return citizen_1.getId() <= citizen_2.getId();
   }

   bool operator>=(Citizen &citizen_1, Citizen &citizen_2) {
       return citizen_1.getId() >= citizen_2.getId();
   }

   bool operator!=(Citizen &citizen_1, Citizen &citizen_2) {
       return citizen_1.getId() != citizen_2.getId();
   }

   bool operator<(Citizen &citizen_1, Citizen &citizen_2) {
       return citizen_1.getId() < citizen_2.getId();
   }

   bool operator>(Citizen &citizen_1, Citizen &citizen_2) {
       return citizen_1.getId() > citizen_2.getId();
   }

   void Citizen::helpForSetInt(int &to_change, const int to_add){
       to_change += to_add;
       if (to_change < 0){
           to_change = 0;
       }
   }
}
