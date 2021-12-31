#include <iostream>
namespace mtm {

    class Citizen {
        const unsigned int id;
        const std::string firstName;
        const std::string lastName;
        const int birthYear;
    public:
        Citizen(const unsigned int id, const std::string firstName, const std::string lastName, const int birthYear):
                                                    id(id), firstName(firstName), lastName(lastName), birthYear(birthYear){}
        ~Citizen() = default;
        virtual Citizen* clone() = 0;

        virtual unsigned int getId() const;
        virtual std::string getFirstName();
        virtual std::string getLastName();
        virtual int getBirthYear();


        virtual void printShort( std::ostream &str ) =0;
        virtual void printLong( std::ostream &str ) = 0;



        friend bool operator==( Citizen &c1, Citizen &c2 );
        friend bool operator<=( Citizen &c1, Citizen &c2 );
        friend bool operator>=( Citizen &c1, Citizen &c2 );
        friend bool operator!=( Citizen &c1, Citizen &c2 );
        friend bool operator<( Citizen &c1, Citizen &c2 );
        friend bool operator>( Citizen &c1, Citizen &c2 );
    };
 } //end namespace