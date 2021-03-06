#ifndef CITIZEN_H // include guard
#define CITIZEN_H
#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <set>

#include "exceptions.h"


namespace mtm {

    class Citizen {
        const int id;
        const std::string firstName;
        const std::string lastName;
        const int birthYear;
    public:
        Citizen(const int id, const std::string firstName, const std::string lastName, const int birthYear):id(id), firstName(firstName), lastName(lastName), birthYear(birthYear){}
        virtual //Ensures provoking the actual object destructor
            ~Citizen() = default;
        Citizen(const Citizen&) = default;
        virtual Citizen* clone() = 0;

        int getId() const;
        std::string getFirstName() const;
        std::string getLastName() const;
        int getBirthYear() const;
        
        virtual void printShort( std::ostream &str ) = 0;
        virtual void printLong( std::ostream &str ) = 0;

        /**
         *
         * @param toChange
         * @param toAdd
         * adds "toAdd" to "toChange", "toChange" stays not negative
         * - used for setSalary
         */
        void helpForSetInt(int &toChange, const int toAdd);

        //all compares are by id
        friend bool operator==( Citizen &c1, Citizen &c2 );
        friend bool operator<=( Citizen &c1, Citizen &c2 );
        friend bool operator>=( Citizen &c1, Citizen &c2 );
        friend bool operator!=( Citizen &c1, Citizen &c2 );
        friend bool operator<( Citizen &c1, Citizen &c2 );
        friend bool operator>( Citizen &c1, Citizen &c2 );
    };
 } //end namespace
#endif