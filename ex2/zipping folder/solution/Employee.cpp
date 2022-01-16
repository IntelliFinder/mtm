#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <set>

#include "exceptions.h"
#include "Skill.h"
#include "Citizen.h"
#include "Employee.h"

namespace mtm{

    int Employee::getSalary() const{
        return salary;
    }

    int Employee::getScore() const{
        return score;
    }

    bool Employee::hasSkill(const int skill_id)  const {
        for(std::set<Skill>::iterator i = skill_set.begin() ; i != skill_set.end(); ++i) {
            if (i->getId() == skill_id){
                return true;
            }
        }
        return false;
    }


    void Employee::learnSkill(Skill const& skill) {
        if(hasSkill(skill.getId())){
            throw mtm::SkillAlreadyLearned();
        }
        if (score<skill.getRequiredPoints()){
            throw CanNotLearnSkill();
        }

        skill_set.insert(skill);
    }

    void Employee::forgetSkill(const int skill_id) {
        for (std::set<Skill>::iterator i = skill_set.begin(); i != skill_set.end(); ++i ) {
            if (i->getId() == skill_id){
                skill_set.erase(i);
                return;
            }
        }
        throw DidNotLearnSkill();
    }

    std::set<Skill> Employee::getCopySkillSet() const{
        std::set<Skill> temp = this->skill_set; //alllocates new memory and copies set
        return temp;
    }



    void Employee::setSalary(const int add_salary) {
        helpForSetInt(salary, add_salary);//here the func is ok
    }

    void Employee::setScore(const int add_score) {
        helpForSetInt(score, add_score); //look! course didn't say what to do in case of score < 0 , snir: good point
    }

    void Employee::printShort(std::ostream &stream){
        stream << getFirstName() + " " + getLastName() << std::endl;
        std::string salaryStr = std::to_string(salary);
        std::string scoreStr = std::to_string(score);
        stream << "Salary: " + salaryStr + " Score: " + scoreStr << std::endl;
    }

    void Employee::printLong(std::ostream& stream) {
        std::string idStr = std::to_string(getId());
        std::string birthYearStr = std::to_string(getBirthYear());
        std::string salaryStr = std::to_string(salary);
        std::string scoreStr = std::to_string(score);
        stream << getFirstName() + " " + getLastName() << std::endl;
        stream << "id - " + idStr + " birth_year - " + birthYearStr << std::endl;
        stream << "Salary: " + salaryStr + " Score: " + scoreStr ;
        if(skill_set.size() != 0){
            stream << " Skills: " << std::endl;
            for (std::set<Skill>::iterator i = skill_set.begin(); i != skill_set.end(); ++i) {
                stream << *i;
            }
        }
        else{
            stream << std::endl;
        }

    }


}

