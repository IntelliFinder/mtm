#include <iostream>

#include "citizen.h"
#include "employee.h"
#include "skill.h"


namespace mtm {

    template <typename Predicate>
    class Faculty {
        const int id;
        Skill skill;
        int addedPoints;
        Predicate pred;
    public:
        Faculty<Predicate>(int id, Skill skill, int addedPoints, Predicate pred):
                                id(id), skill(skill), addedPoints(addedPoints), pred(pred);

        ~Faculty() = default;

        Employee& teach(Employee& emp);
    };
}