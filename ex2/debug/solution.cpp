#include <iostream>
#include <string>

#include "skill.h"
#include "citizen.h"
#include "employee.h"
#include "manager.h"

#include "exceptions.h"

using namespace mtm;
/**==========================SKILL=========================================**/
int Skill::getId() const { return id; }

std::string Skill::getName() const { return name; }

int Skill::requiredPoints() const { return points; }

Skill& Skill::operator++() {
    points = points + 1;
    return *this;
}

Skill& Skill::operator+=(const int amount) {
    if (amount<0){
        throw NegativePoints();
    }
    points = points + amount;
    return *this;
}
Skill &Skill::operator+(int amount){
    *this += amount;
    return *this;
}


std::ostream& operator<<(std::ostream &os, const Skill &sk) {
    os << sk.getName(); // without << std::endl
    return os;
}


bool operator>(const Skill& sk1, const Skill& sk2){
    return sk1.getId() > sk2.getId();
}

bool operator<(const Skill& sk1, const Skill& sk2){
    return sk1.getId() < sk2.getId();
}

bool operator!=(const Skill& sk1, const Skill& sk2){
    return sk1.getId() != sk2.getId();
}

bool operator>=(const Skill& sk1, const Skill& sk2){
    return sk1.getId() >= sk2.getId();
}

bool operator<=(const Skill& sk1, const Skill& sk2){
    return sk1.getId() <= sk2.getId();
}

bool operator==(const Skill& sk1, const Skill& sk2){
    return sk1.getId() == sk2.getId();
}




/**=============================END SKILL=========================================**/

/**===============================CITIZEN=========================================**/
int Citizen::getId() const { return id; }
std::string Citizen::getFirstName() const {
    return firstName;
}
std::string Citizen::getLastName() const {
    return lastName;
}
int Citizen::getBirthYear() const {
    return birthYear;
}
void Citizen::printShort( std::ostream &str) {
    str<<std::endl; //placeholder
}
void Citizen::printLong( std::ostream &str ){
    str<<std::endl; //placeholder
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
/**========================END CITIZEN=========================================**/
/**============================EMPLOYEE=========================================**/
int Employee::getSalary() const{
    return salary;
}

int Employee::getScore() const{
    return score;
}
bool Employee::hasSkill(const int skillId) {
    for(std::set<Skill>::iterator i = skillSet.begin() ; i != skillSet.end(); ++i) {
        if (i->getId() == skillId){
            skillSet.erase(i);
            return true;
        }
    }
    return false;
}

/*
void Employee::learnSkill(Skill& skill) {
    if (score<skill.requiredPoints()){
        throw CanNotLearnSkill();
    }
    if(hasSkill(skill.getId())){
        throw SkillAlreadyLearned();
    }
   skillSet.insert(skill);//bug here
}
*/
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
    os << "id - " + idStr + " birth_year - " + birthYearStr;
    os << "Salary: " + salaryStr + " Score: " + scoreStr + " Skills: "<< std::endl;
    for (std::set<Skill>::iterator i = skillSet.begin(); i!=skillSet.end(); ++i) {
        os << i->getName() << std::endl; //ERROR overloading doesn't work
    }
}
/**========================END EMPLOYEE=========================================**/

/**============================MANAGER=========================================**/
int Manager::getSalary() const {
    return this->salary;
}

void Manager::addEmployee(Employee *employeeToAdd) {
    for (std::list<Employee*>::iterator employeeItr = employeesList.begin();employeeItr != employeesList.end(); employeeItr++) {
        if ((*employeeToAdd).getId() == (*employeeItr)->getId()){
            throw EmployeeAlreadyHired();
        }
    }
    //employee isn't hired
    employeesList.push_back(employeeToAdd);
}

void Manager::removeEmployee(const int id) {
    for (std::list<Employee*>::iterator employeeItr = employeesList.begin();employeeItr != employeesList.end(); employeeItr++) {
        if ((*employeeItr)->getId() == id){
            employeesList.erase(employeeItr);
            return;
        }
    }
    throw EmployeeIsNotHired();
}

void Manager::setSalary(const int addSalary) {
    helpForSetInt(salary,addSalary);
}

void Manager::printShort(std::ostream &os) {
    std::string idStr = std::to_string(getId());
    std::string birthYearStr = std::to_string(getBirthYear());
    std::string salaryStr = std::to_string(salary);
    os << getFirstName() + " " + getLastName()<<std::endl;
    os << "id - " + idStr + " birth_year - " + birthYearStr;
    os << "Salary: " + salaryStr << std::endl; //look! code duplication, maybe we should create a function
}

void Manager::printLong(std::ostream &os) {
    printShort(os);
    for (std::list<Employee*>::iterator employeeItr = employeesList.begin();employeeItr != employeesList.end(); employeeItr++) {
        (*employeeItr)->printShort(os);
    }
}



/**========================END MANAGER=========================================**/
