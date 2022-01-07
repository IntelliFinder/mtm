#include <iostream>
#include <string>

#include "skill.h"
#include "citizen.h"
#include "employee.h"
#include "manager.h"
#include "workplace.h"
/**==========================SKILL=========================================**/

namespace mtm{
    /*
    struct NegativePoints : public std::exception
            //Im not sure that this is the way it's supposed tp be
    {
        const char * what () const throw ()//look! I hope char* is ok even though we shouldnt use it
        {
            return "NegativePoints";
        }
    };
    */
    unsigned int Skill::getId() const { return id; }

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
        return !(sk1<sk2); //more efficient
    }

    bool operator<=(const Skill sk1, const Skill sk2){
        return !(sk1>sk2);
    }

    bool operator==(const Skill sk1, const Skill sk2){
        return !(sk1 != sk2);
    }


}



/**=============================END SKILL=========================================**/

/**===============================CITIZEN=========================================**/
namespace mtm{
    unsigned int Citizen::getId() const { return id; }
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



}
/**========================END CITIZEN=========================================**/

/**============================EMPLOYEE=========================================**/
namespace mtm{
   /*
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
   */

    int Employee::getSalary() const{
        return salary;
    }

    int Employee::getScore() const{
        return score;
    }
    bool Employee::hasSkill(const int skillId) {
        for (std::set<Skill>::iterator skillPtr = skillSet.begin(); skillPtr!=skillSet.end() ; skillPtr) {
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
        for (std::set<Skill>::iterator skillPtr = skillSet.begin(); skillPtr!=skillSet.end() ; skillPtr) {
            if (skillPtr->getId() == skillId){
                skillSet.erase(skillPtr);
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
        for (std::set<Skill>::iterator skillPtr = skillSet.begin(); skillPtr!=skillSet.end() ; skillPtr) {
            os << *skillPtr << std::endl;
        }
    }


}

/**========================END EMPLOYEE=========================================**/

/**============================MANAGER=========================================**/

namespace mtm{
    /*
    struct EmployeeAlreadyHired : public std::exception
        //Im not sure that this is the way it's supposed tp be
    {
        const char * what () const throw ()//look! I hope char* is ok even though we shouldnt use it
        {
            return "EmployeeAlreadyHired";
        }
    };
    struct EmployeeIsNotHired : public std::exception
        //Im not sure that this is the way it's supposed tp be
    {
        const char * what () const throw ()//look! I hope char* is ok even though we shouldnt use it
        {
            return "EmployeeIsNotHired";
        }
    };
     */

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



}

/**========================END MANAGER=========================================**/

/**========================WORKPLACE===========================================**/
namespace mtm {
    bool Workplace::isManagerHired(const int managerId) {
        for(Manager *runManager:managersList){
            if ((*runManager).getId() == managerId){
                return true;
            }
        }
        return false;
    }
    int Workplace::getId() {
        return id;
    }

    std::string Workplace::getName() {
        return name;
    }

    int Workplace::getWorkersSalary() {
        return workersSalary;
    }

    int Workplace::getManagersSalary() {
        return managersSalary;
    }

    void Workplace::hireManager(Manager *managerAdd) {
        if(isManagerHired(managerAdd->getId())){
            throw ManagerAlreadyHired();
        }
        if (managerAdd->isHired){
            throw CanNotHireManager();
        }
        managerAdd->isHired = true;
        managersList.push_back(managerAdd);
    }

    void Workplace::fireEmployee(const int employeeId, const int managerId) {
        if(!isManagerHired(managerId)){
            throw ManagerIsNotHired();
        }
        Manager *manager = getPointerToManager(managerId);
        manager->removeEmployee(employeeId);

    }

    void Workplace::fireManager(const int managerId) {
        if(!isManagerHired(managerId)){
            throw ManagerIsNotHired();
        }
        Manager *manager = getPointerToManager(managerId);
        manager->isHired = false;
        managersList.remove(manager);
    }

    Manager *Workplace::getPointerToManager(const int managerId) {
        for(Manager *runManager:managersList){
            if ((*runManager).getId() == managerId){
                return runManager;
            }
        }
        return nullptr;
    }
    std::ostream &operator<<(std::ostream &os, const Workplace &workplace) {
        os << "Workplace name - " << workplace.name<< " Groups:";
        //look! not sure where endl should be
        for (Manager *pManager : workplace.managersList){
            os<<std::endl;
            pManager->printLong(os);
        }
        //endl here doesn't seem right
        return os;
    }
    /*bool Workplace::isEmployeeHired(Employee *pEmployee, const int managerId) {
         Manager *trueManager;
         for(Manager *runManager:managersList){
             if ((*runManager).getId() == managerId){
                 trueManager = runManager;
             }
         }
         trueManager->addEmployee(pEmployee);
     }*/



}

/**========================END WORKPLACE=========================================**/

/**============================CITY=========================================**/

/**========================END CITY=========================================**/


/**============================FACULTY=========================================**/
/**========================END FACULTY=========================================**/
