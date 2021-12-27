#include <iostream>

#include "skill.h"
#include "citizen.h"

/**==========================SKILL=========================================**/
/**operator ++(  );
/**operator +=( const int amount );
/**operator +( const int amount );**/
namespace mtm{

    Skill& Skill::operator+=(const int amount) {
        points += amount;
        return *this;
    }
    Skill& Skill::operator++(){
        points=points+1;
        return *this;
    }

    Skill::Skill(const unsigned int id, const char *name, int points, double pro) : id(id), name(name), points(points), pro(pro) {}
}



/**=======================END SKILL=========================================**/
