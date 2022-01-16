#ifndef FACULTY_H // include guard
#define FACULTY_H
#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <set>

#include "exceptions.h"
#include "Skill.h"
#include "Citizen.h"
#include "Employee.h"
#include "Manager.h"

class Condition{
public:
    virtual bool operator()(mtm::Employee* employee)=0;
};
namespace mtm {

    template <typename Predicate>
    class Faculty {
        const int id;
        Skill skill;
        int added_points;
        Predicate* pred;
    public:
        Faculty<Predicate>(int id, Skill skill, int addedPoints, Predicate* pred):
                id(id), skill(skill), added_points(addedPoints), pred(pred){}

        ~Faculty() = default;
        /**
         * teach: teaches an employee a skill taught by faculty , adds score acquired by skill
         * @param employee
         * teches employee
         */
        void teach(Employee* employee){
            if(!(*pred)(employee)){
                throw EmployeeNotAccepted();
            }
            employee->setScore(added_points);
            employee->learnSkill(skill);
        }

        Skill getSkill() const{
            return skill;
        }

        int getId() const{
            return id;
        }
        int getAddedPoints() const{
            return added_points;
        }
    };
}
#endif
