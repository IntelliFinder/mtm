
#ifndef __EMPLOYEE__H__
#define __EMPLOYEE__H__
#include <iostream>
#include <memory>
#include <string>
#include <list>

#include "exceptions.h"
#include "Skill.h"
#include "Citizen.h"


namespace mtm {

    class Employee : public Citizen {
        int salary; //course says int
        int score;
        std::set<Skill> skillSet;
        std::set<Skill> getCopySkillSet() const;

    public:
        Employee(const unsigned int id, const std::string firstName, const std::string lastName, const int birthYear):
            Citizen(id, firstName, lastName, birthYear), salary(0),score(0), skillSet() {}
        Employee(const Employee& emp):
            Citizen(emp.getId(), emp.getFirstName(), emp.getLastName(), emp.getBirthYear()), salary(0),score(0), skillSet(emp.getCopySkillSet()) {};
        ~Employee() = default ;
        Employee* clone() override{//not sure about type here I think it should be Citizen*
            return new Employee(*this); //need to change copy constructor so it includes the skill set
        }
        int getSalary() const;
        int getScore() const;
        void learnSkill(Skill const& skill);
        void forgetSkill(const int skillId);
        bool hasSkill(const int skillId) const;
        void setSalary(const int addSalary);
        void setScore(const int addScore);
        void printShort(std::ostream &os) override;
        void printLong(std::ostream &os) override;



    };
}
#endif
