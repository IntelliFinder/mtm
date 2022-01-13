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

    bool Employee::hasSkill(const int skillId)  const {
        for(std::set<Skill>::iterator i = skillSet.begin() ; i != skillSet.end(); ++i) {
            if (i->getId() == skillId){
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

        skillSet.insert(skill);
    }

    void Employee::forgetSkill(const int skillId) {
        for ( std::set<Skill>::iterator i = skillSet.begin(); i!=skillSet.end(); ++i ) {
            if (i->getId() == skillId){
                skillSet.erase(i);
                return;
            }
        }
        throw DidNotLearnSkill();
    }

    std::set<Skill> Employee::getCopySkillSet() const{
        std::set<Skill> temp = this->skillSet; //alllocates new memory and copies set
        return temp;
    }



    void Employee::setSalary(const int addSalary) {
        helpForSetInt(salary,addSalary);//here the func is ok
    }

    void Employee::setScore(const int addScore) {
        helpForSetInt(score,addScore); //look! course didn't say what to do in case of score < 0 , snir: good point
    }

    void Employee::printShort(std::ostream &os){
        os <<getFirstName() + " " + getLastName()<<std::endl;
        std::string salaryStr = std::to_string(salary);
        std::string scoreStr = std::to_string(score);
        os << "Salary: " + salaryStr + " Score: " + scoreStr << std::endl;
    }

    void Employee::printLong(std::ostream& os) {
        std::string idStr = std::to_string(getId());
        std::string birthYearStr = std::to_string(getBirthYear());
        std::string salaryStr = std::to_string(salary);
        std::string scoreStr = std::to_string(score);
        os << getFirstName() + " " + getLastName()<<std::endl;
        os << "id - " + idStr + " birth_year - " + birthYearStr<<std::endl;
        os << "Salary: " + salaryStr + " Score: " + scoreStr ;
        if(skillSet.size()!=0){
            os<<" Skills: "<< std::endl;
            for (std::set<Skill>::iterator i = skillSet.begin(); i!=skillSet.end(); ++i) {
                os << i->getName() << std::endl; //ERROR overloading doesn't work
            }
        }
        else{
            os<<std::endl;
        }

    }


}

