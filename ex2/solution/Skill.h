#ifndef SKILL_H // include guard
#define SKILL_H
#include <iostream>
#include <set>

#include "exceptions.h"
namespace mtm {

    class Skill {
        const int id;
        const std::string name;
        int points; //points needed to acquire skill
    public:
        Skill(const int id, const std::string name, int points);

        Skill(const Skill& skill);

        Skill &operator=(const Skill& skill);

        ~Skill() = default;

        int getId() const;

        std::string getName() const;

        int getRequiredPoints() const;

        //plus operators
        Skill operator++(int );

        Skill &operator+=(int amount);

        //friend zone ;D
        //operators used by other clsses
        friend Skill operator+(Skill const& sk1, int amount);

        friend Skill operator+(int amount, Skill const& sk1);

        /**
         * prints name of skill with end line
         * @param os
         * @param sk
         * @return ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const Skill& sk);
        //compare operators, compare is by id

        friend bool operator>( Skill const& sk1,  Skill const& sk2);
        friend bool operator<(mtm::Skill const&, mtm::Skill const&);







        friend bool operator==( Skill const& sk1,  Skill const& sk2);
     };

    bool operator!=( Skill const& sk1,  Skill const& sk2);

    bool operator>=( Skill const& sk1,  Skill const& sk2);

    bool operator<=( Skill const& sk1,  Skill const& sk2);

} //end namespace
#endif