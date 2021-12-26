#include <iostream>

#include "skill.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
/**=======================SKILL=========================================**/
/**operator ++(  );
/**operator +=( const int amount );
/**operator +( const int amount );**/

Skill& Skill::operator+=(const int amount) {
    points += amount;
    return *this;
}
Skill& Skill::operator++(){
    points++;
    return *this;
}


/**=======================END SKILL=========================================**/
