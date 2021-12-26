#include <iostream>

class Skill{
    const unsigned int id;
    std::string name;
    const int points;
    const double pro;
public:
    Skill(const unsigned int id, const char* name, const int points, const double pro);
    int getId();
    std::string getName();
    int requiredPoints();

    Skill& operator++();
    Skill& operator+=( const int amount );
    Skill operator+( const int amount );
    //print operators

};

//print operators

//std operators
Skill operator>( const Skill sk1, const Skill sk2 );
Skill operator<( const Skill sk1, const Skill sk2 );
Skill operator!=( const Skill sk1, const Skill sk2 );
Skill operator>=( const Skill sk1, const Skill sk2 );
Skill operator<=( const Skill sk1, const Skill sk2 );
Skill operator==( const Skill sk1, const Skill sk2 );
