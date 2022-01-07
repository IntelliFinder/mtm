#include <iostream>

#include "citizen.h"
#include "skill.h"
#include <set>

namespace mtm {

    class Employee : public Citizen {
        int salary; //course says int
        int score;
        std::set<Skill> skillSet;

    public:
        Employee(const unsigned int id, const std::string firstName, const std::string lastName, const int birthYear):
            Citizen(id, firstName, lastName, birthYear), salary(0),score(0), skillSet() {}
        Employee(const Employee& emp):
            Citizen(emp.getId(), emp.getFirstName(), emp.getLastName(), emp.getBirthYear()), salary(0),score(0), skillSet(emp.getCopySkillSet()) {};
        ~Employee() = default ;
        Citizen* clone(){
            return new Employee(*this); //need to change copy constructor so it includes the skill set
        }
        int getSalary() const;
        int getScore() const;
        std::set<Skill> getCopySkillSet() const;
        void learnSkill(const Skill skill);
        void forgetSkill(const int skillId);
        bool hasSkill(const int skillId);
        void setSalary(const int addSalary);
        void setScore(const int addScore);
        void printShort(std::ostream &os) override;
        void printLong(std::ostream &os) override;



    };
}