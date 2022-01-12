#ifndef FACULTY_H // include guard
#define FACULTY_H
#include <iostream>
#include "Employee.h"
#include "Skill.h"
class Condition{
public:
    virtual bool operator()(mtm::Employee* employee)=0;
};
namespace mtm {

    template <typename Predicate>
    class Faculty {
        const int id;
        Skill skill;
        int addedPoints;
        Predicate* pred;
    public:
        Faculty<Predicate>(int id, Skill skill, int addedPoints, Predicate* pred):
                                id(id), skill(skill), addedPoints(addedPoints), pred(pred){}

        ~Faculty() = default;

        void teach(Employee* emp){
            /*if(emp.hasSkill(skill.getId())){
                return emp;
            }*/
            if(!(*pred)(emp)){
                throw EmployeeNotAccepted();
            }
            emp->setScore(addedPoints); //added score
            emp->learnSkill(skill); //adds skill already checked emp doesnt ahve it already
            //return emp;
        }

        Skill getSkill() const{
            return skill;
        }

        int getId() const{
            return id;
        }
        int getAddedPoints() const{
            return addedPoints;
        }
    };
}
#endif
