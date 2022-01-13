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

        virtual int getId() const;
        virtual std::string getFirstName() const;
        virtual std::string getLastName() const;
        virtual int getBirthYear() const;
        
        virtual void printShort( std::ostream &str ) = 0;
        virtual void printLong( std::ostream &str ) = 0;


        void helpForSetInt(int &toChange, const int toAdd);

        friend bool operator==( Citizen &c1, Citizen &c2 );
        friend bool operator<=( Citizen &c1, Citizen &c2 );
        friend bool operator>=( Citizen &c1, Citizen &c2 );
        friend bool operator!=( Citizen &c1, Citizen &c2 );
        friend bool operator<( Citizen &c1, Citizen &c2 );
        friend bool operator>( Citizen &c1, Citizen &c2 );
    };
 } //end namespace
#endif