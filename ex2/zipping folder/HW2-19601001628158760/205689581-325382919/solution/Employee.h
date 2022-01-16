
#ifndef __EMPLOYEE__H__
#define __EMPLOYEE__H__
#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <set>

#include "exceptions.h"
#include "Skill.h"
#include "Citizen.h"


namespace mtm {

    class Employee : public Citizen {
        int salary; //course says int
        int score;
        std::set<Skill> skill_set;
        std::set<Skill> getCopySkillSet() const;

    public:
        Employee(const unsigned int id, const std::string first_name, const std::string last_name, const int birth_year):
                Citizen(id, first_name, last_name, birth_year), salary(0), score(0), skill_set() {}
        Employee(const Employee& emp):
                Citizen(emp.getId(), emp.getFirstName(), emp.getLastName(), emp.getBirthYear()), salary(0), score(0), skill_set(emp.getCopySkillSet()) {};
        ~Employee() = default ;
        Employee* clone() override{//not sure about type here I think it should be Citizen*
            return new Employee(*this); //need to change copy constructor so it includes the skill set
        }
        int getSalary() const;
        int getScore() const;
        void learnSkill(Skill const& skill);
        void forgetSkill(const int skill_id);
        bool hasSkill(const int skill_id) const;
        void setSalary(const int add_salary);
        void setScore(const int add_score);
        /**
         * prints <full name>
         * Salary: <Salary> Score: <Score>
         * @param stream
         */
        void printShort(std::ostream &stream) override;
        /**
         * prints <full name>
         * id - <id> birth_year - <birth_year>
         * Salary: <Salary> Score: <Score> Skills:
         * <all skills>
         * @param stream
         */
        void printLong(std::ostream &stream) override;



    };
}
#endif
