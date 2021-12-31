#include <iostream>
#include <string>

#include "skill.h"
#include "citizen.h"
#include "employee.h"
/**==========================SKILL=========================================**/

namespace mtm{
    struct NegativePoints : public std::exception
            //Im not sure that this is the way it's supposed tp be
    {
        const char * what () const throw ()//look! I hope char* is ok even though we shouldnt use it
        {
            return "NegativePoints";
        }
    };

    unsigned int Skill::getId() const { return id; }

    std::string Skill::getName() const { return name; }

    int Skill::requiredPoints() const { return points - pro; }

    Skill& Skill::operator++() {
        points = points + 1;
        return *this;
    }

    Skill& Skill::operator+=(const int amount) {
        if (amount<0)
            throw NegativePoints();
        points = points + amount;
        return *this;
    }
    Skill &Skill::operator+(int amount){
        *this += amount;
        return *this;
    }


    std::ostream &operator<<(std::ostream &os, const Skill &sk) {
        os << sk.getName(); // without << std::endl
        return os;
    }


    bool operator>(const Skill sk1, const Skill sk2){
        return sk1.getId() > sk2.getId();
    }

    bool operator<(const Skill sk1, const Skill sk2){
        return sk1.getId() < sk2.getId();
    }

    bool operator!=(const Skill sk1, const Skill sk2){
        return sk1.getId() != sk2.getId();
    }

    bool operator>=(const Skill sk1, const Skill sk2){
        return sk1.getId() >= sk2.getId();
    }

    bool operator<=(const Skill sk1, const Skill sk2){
        return sk1.getId() <= sk2.getId();
    }

    bool operator==(const Skill sk1, const Skill sk2){
        return sk1.getId() == sk2.getId();
    }


}



/**=============================END SKILL=========================================**/

/**===============================CITIZEN=========================================**/
namespace mtm{
    unsigned int Citizen::getId() const { return id; }
    std::string Citizen::getFirstName(){
        return firstName;
    }
    std::string Citizen::getLastName(){
        return lastName;
    }
    int Citizen::getBirthYear(){
        return birthYear;
    }
    void Citizen::printShort( std::ostream &str) {
        str<<std::endl; //placeholder
    }
    void Citizen::printLong( std::ostream &str ){
        str<<std::endl; //placeholder
    }

    /*Citizen::Citizen(const Citizen &citizen) :  id(citizen.id), firstName(citizen.firstName),
                                                lastName(citizen.lastName), birthYear(citizen.birthYear){
    }*/

    Citizen *Citizen::clone() {
        Citizen *citizenPtr = new Citizen(*this);
        return citizenPtr;
    }

    bool operator==(Citizen &c1, Citizen &c2) {
        return c1.getId() == c2.getId();
    }

    bool operator<=(Citizen &c1, Citizen &c2) {
        return c1.getId() <= c2.getId();
    }
    bool operator>=(Citizen &c1, Citizen &c2) {
        return c1.getId() >= c2.getId();
    }

    bool operator!=(Citizen &c1, Citizen &c2) {
        return c1.getId() != c2.getId();
    }

    bool operator<(Citizen &c1, Citizen &c2) {
        return c1.getId() < c2.getId();
    }

    bool operator>(Citizen &c1, Citizen &c2) {
        return c1.getId() > c2.getId();
    }




}
/**========================END CITIZEN=========================================**/

/**============================EMPLOYEE=========================================**/
namespace mtm{
    struct SkillAlreadyLearned : public std::exception
        //Im not sure that this is the way it's supposed tp be
    {
        const char * what () const throw ()//look! I hope char* is ok even though we shouldnt use it
        {
            return "SkillAlreadyLearned";
        }
    };
    struct CanNotLearnSkill : public std::exception
        //Im not sure that this is the way it's supposed tp be
    {
        const char * what () const throw ()//look! I hope char* is ok even though we shouldnt use it
        {
            return "CanNotLearnSkill";
        }
    };
    struct DidNotLearnSkill : public std::exception
        //Im not sure that this is the way it's supposed tp be
    {
        const char * what () const throw ()//look! I hope char* is ok even though we shouldnt use it
        {
            return "DidNotLearnSkill";
        }
    };


    int Employee::getSalary(){
        return salary;
    }

    int Employee::getScore() {
        return score;
    }
    bool Employee::hasSkill(const int skillId) {
        for (auto skillPtr = skillSet.begin(); skillPtr!=skillSet.end() ; skillPtr) {
            if (skillPtr->getId() == skillId){
                skillSet.erase(skillPtr);
                return true;
            }
        }
        return false;
    }
    void Employee::learnSkill(const Skill skill) {
        if (score<skill.requiredPoints()){
            throw CanNotLearnSkill();
        }
        if(hasSkill(skill.getId())){
            throw SkillAlreadyLearned();
        }
        skillSet.insert(skill);
        return ;//because its void
    }

    void Employee::forgetSkill(const int skillId) {
        for (auto skillPtr = skillSet.begin(); skillPtr!=skillSet.end() ; skillPtr) {
            if (skillPtr->getId() == skillId){
                skillSet.erase(skillPtr);
                return;
            }
        }
        throw DidNotLearnSkill();
    }

    void helpForSetInt(int &toChange, const int toAdd){
        toChange += toAdd;
        if (toChange < 0){
            toChange = 0;
        }
    }
    void Employee::setSalary(const int addSalary) {
        helpForSetInt(salary,addSalary);//here the func is ok
    }

    void Employee::setScore(const int addScore) {
        helpForSetInt(score,addScore); //look! course didn't say what to do in case of score < 0
    }

    void Employee::printShort(std::ostream &os){
        os <<getFirstName() + " " + getLastName()<<std::endl;
        std::string salaryStr = std::to_string(salary);
        std::string scoreStr = std::to_string(score);
        os << "Salary: " + salaryStr + " Score: " + scoreStr << std::endl;
    }

    void Employee::printLong(std::ostream &os) {
        std::string idStr = std::to_string(getId());
        std::string birthYearStr = std::to_string(getBirthYear());
        std::string salaryStr = std::to_string(salary);
        std::string scoreStr = std::to_string(score);
        os << getFirstName() + " " + getLastName()<<std::endl;
        os << "id - " + idStr + " birth_year - " + birthYearStr;
        os << "Salary: " + salaryStr + " Score: " + scoreStr + " Skills: "<< std::endl;
        for (auto skillPtr = skillSet.begin(); skillPtr!=skillSet.end() ; skillPtr) {
            os << *skillPtr << std::endl;
        }
    }


}

/**========================END EMPLOYEE=========================================**/

/**============================MANAGER=========================================**/
/**========================END MANAGER=========================================**/

/**============================CITY=========================================**/
/**========================END CITY=========================================**/


/**============================FACULTY=========================================**/
/**========================END FACULTY=========================================**/
