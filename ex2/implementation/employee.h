#include <iostream>

#include "citizen.h"
#include "skill.h"
#include <set>

namespace mtm {

    class Employee : public Citizen {
        double salary;
        double score;
        std::set<Skill> skillSet;
        bool hasSkill(const Skill skill);

    public:
        Employee(const unsigned int id, const std::string firstName, const std::string lastName, const int birthYear)
            : Citizen(id, firstName, lastName, birthYear), salary(0),score(0), skillSet() {}

        ~Employee() = default;
        double getSalary();
        double getScore();
        void learnSkill(const Skill skill);
        void forgetSkill(const int skillId);
    };
}