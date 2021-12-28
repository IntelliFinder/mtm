#include <iostream>
namespace mtm {

    class Citizen {
        const unsigned int id;
        const std::string firstName;
        const std::string lastName;
        const int birthYear;
    public:
        Citizen(const unsigned int id, const std::string firstName, const std::string lastName, const int birthYear);
        ~Citizen();

        unsigned int getId() const;

        std::string getFirstName();
        std::string getLastName();
        int getBirthYear();
        /*
        virtual void printShort( std::ostream ) ;
        virtual void printLong( std::ostream );
        virtual void clone();
        */
    };

/*
    Citizen operator==( Citizen c1, Citizen c2 );
    Citizen operator<=( Citizen c1, Citizen c2 );
    Citizen operator>=( Citizen c1, Citizen c2 );
    Citizen operator!=( Citizen c1, Citizen c2 );
    Citizen operator<( Citizen c1, Citizen c2 );
    Citizen operator>( Citizen c1, Citizen c2 );
*/
 } //end namespace