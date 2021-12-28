#include <iostream>
namespace mtm {

    class Citizen {
        const unsigned int id;
        const std::string firstName;
        const std::string lastName;
        const int birthYear;
    public:
        Citizen(const unsigned int id, const std::string firstName, const std::string lastName, const int birthYear);
        ~Citizen() = default;

        unsigned int getId() const;

        std::string getFirstName();
        std::string getLastName();
        int getBirthYear();

        virtual void printShort( std::ostream str ) ;
        virtual void printLong( std::ostream str );
        virtual void clone() = 0;

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