#include <iostream>
namespace mtm {

    class Citizen {
        const int id;
        const std::string firstName;
        const std::string lastName;
        const int birthYear;
    public:
        int getId();
        std::string getFirstName();
        std::string getLastName();
        int getBirthYear();
        virtual printShort( std::ostream ) ;
        virtual printLong( std::ostream );
        virtual clone();

    };


    Citizen operator==( Citizen c1, Citizen c2 );
    Citizen operator<=( Citizen c1, Citizen c2 );
    Citizen operator>=( Citizen c1, Citizen c2 );
    Citizen operator!=( Citizen c1, Citizen c2 );
    Citizen operator<( Citizen c1, Citizen c2 );
    Citizen operator>( Citizen c1, Citizen c2 );
} //end namespace