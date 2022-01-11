#include <iostream>
#include <memory>
#include <string>
#include <list>

#include "Skill.h"
#include "Citizen.h"
#include "Employee.h"
#include "Manager.h"
#include "Workplace.h"
#include "Faculty.h"
#include "City.h"
#include "exceptions.h"

using namespace mtm;
/**==========================SKILL=========================================**/
Skill::Skill(const int id, const std::string name, int points) : id(id), name(name), points(points)
{
}

int Skill::getId() const { return id; }

std::string Skill::getName() const { return name; }

int Skill::getRequiredPoints() const { return points; }
namespace mtm{
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


    bool operator>( Skill const& sk1,  Skill const& sk2){
        return sk1.getId() > sk2.getId();
    }

    bool operator<( mtm::Skill const& sk1,  mtm::Skill const& sk2){
        return sk1.getId() < sk2.getId();
    }

    bool operator!=( Skill const& sk1,  Skill const& sk2){
        return sk1.getId() != sk2.getId();
    }

    bool operator>=( Skill const& sk1,  Skill const& sk2){
        return sk1.getId() >= sk2.getId();
    }

    bool operator<=( Skill const& sk1,  Skill const& sk2){
        return sk1.getId() <= sk2.getId();
    }

    bool operator==( Skill const& sk1,  Skill const& sk2){
        return sk1.getId() == sk2.getId();
    }
}
/*
bool mtm::operator>( Skill const& sk1,  Skill const& sk2){
    return sk1.getId() > sk2.getId();
}

bool mtm::operator<( mtm::Skill const& sk1,  mtm::Skill const& sk2){
    return sk1.getId() < sk2.getId();
}

bool mtm::operator!=( Skill const& sk1,  Skill const& sk2){
    return sk1.getId() != sk2.getId();
}

bool mtm::operator>=( Skill const& sk1,  Skill const& sk2){
    return sk1.getId() >= sk2.getId();
}

bool mtm::operator<=( Skill const& sk1,  Skill const& sk2){
    return sk1.getId() <= sk2.getId();
}

bool mtm:: operator==( Skill const& sk1,  Skill const& sk2){
    return sk1.getId() == sk2.getId();
}*/






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


void Employee::learnSkill(Skill const& skill) {
    if (score<skill.getRequiredPoints()){
        throw CanNotLearnSkill();
    }
    if(hasSkill(skill.getId())){
        throw SkillAlreadyLearned();
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
    os << "id - " + idStr + " birth_year - " + birthYearStr<<std::endl;
    os << "Salary: " + salaryStr + " Score: " + scoreStr + " Skills: "<< std::endl;
    for (std::set<Skill>::iterator i = skillSet.begin(); i!=skillSet.end(); ++i) {
        os << i->getName() << std::endl; //ERROR overloading doesn't work
    }
}
/**========================END EMPLOYEE=========================================**/

/**============================MANAGER=========================================**/

Manager::Manager(const Manager& manager):Citizen(manager.getId(),manager.getFirstName(),manager.getLastName(),manager.getBirthYear())
,salary(manager.getSalary()),employeesList(),isHired(false){
    for (Employee* pRunEmployee:manager.employeesList) {
        employeesList.push_back(pRunEmployee);
    }
}
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
void Manager::removeEmployeeAndSalary(const int id,int salaryToMinus) {//salaryToMinus>0
    for (std::list<Employee*>::iterator employeeItr = employeesList.begin();employeeItr != employeesList.end(); employeeItr++) {
        if ((*employeeItr)->getId() == id){
            employeesList.erase(employeeItr);
            (*employeeItr)->setSalary(-salaryToMinus);
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
    os << "id - " + idStr + " birth_year - " + birthYearStr<<std::endl;
    os << "Salary: " + salaryStr << std::endl; //look! code duplication, maybe we should create a function
}

void Manager::printLong(std::ostream &os) {
    printShort(os);
    os << "Employees:"<<std::endl;
    for (std::list<Employee*>::iterator employeeItr = employeesList.begin();employeeItr != employeesList.end(); employeeItr++) {
        (*employeeItr)->printShort(os);
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
    int Workplace::getId() const{
        return id;
    }

    std::string Workplace::getName() const {
        return name;
    }

    int Workplace::getWorkersSalary() const{
        return workersSalary;
    }

    int Workplace::getManagersSalary() const{
        return managersSalary;
    }

    void Workplace::hireManager(Manager *managerAdd) {
        if(isManagerHired(managerAdd->getId())){
            throw ManagerAlreadyHired();
        }
        if (managerAdd->isHired){
            throw CanNotHireManager();
        }
        managersList.push_back(managerAdd);
        managerAdd->isHired = true;
        managerAdd->setSalary(managersSalary);
    }

    void Workplace::fireEmployee(const int employeeId, const int managerId) {
        if(!isManagerHired(managerId)){
            throw ManagerIsNotHired();
        }
        Manager *manager = getPointerToManager(managerId);
        manager->removeEmployeeAndSalary(employeeId,workersSalary);//should be positive
    }

    void Workplace::fireManager(const int managerId) {
        if(!isManagerHired(managerId)){
            throw ManagerIsNotHired();
        }
        Manager *manager = getPointerToManager(managerId);
        manager->isHired = false;
        manager->setSalary(-managersSalary);
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
        os << "Workplace name - " << workplace.name;
        //look! not sure where endl should be
        if (!workplace.managersList.empty()){
            os<< " Groups:";
        }
        for (Manager *pManager : workplace.managersList){
            os<<std::endl;
            pManager->printLong(os);
        }
        //endl here doesn't seem right because short print does it for us
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

/**============================FACULTY=========================================**/\
/*
namespace mtm{
    template<typename Predicate>
    Employee& Faculty<Predicate>::teach(Employee& emp){
        if(emp.hasSkill(skill.getId())){
            return emp;
        }
        if(!pred(emp)){
            throw EmployeeNotAccepted();
        }
        emp.setScore(addedPoints); //added score
        emp.learnSkill(skill); //adds skill already checked emp doesnt ahve it already
        return emp;
    }

    template<typename Predicate>
    Skill Faculty<Predicate>::getSkill() const{
        return skill;
    }

    template<typename Predicate>
    int Faculty<Predicate>::getId() const {
        return id;
    }

    template<typename Predicate>
    int Faculty<Predicate>::getAddedPoints() const{
        return addedPoints;
    }

}*/
/**========================END FACULTY=========================================**/
/**=======================City==================================================**/
namespace mtm{

    bool City::isCitizenExist(const int id, const std::list<std::shared_ptr<Citizen>>& citizenList){
        for (const std::shared_ptr<Citizen>& runCitizen:citizenList){
            if (runCitizen->getId() == id){
                return true;
            }
        }
        return false;
    }
    void City::addEmployee(const int employeeId, const std::string firstName, const std::string lastName, const int birthYear) {
        if (isCitizenExist(employeeId, employeesList)){
            throw CitizenAlreadyExists();
        }
        employeesList.push_back(std::make_shared<Employee>(employeeId, firstName, lastName, birthYear));
    }

    void City::addManager(const int managerId, const std::string firstName, const std::string lastName, const int birthYear) {
        if (isCitizenExist(managerId, managersList)){
            throw CitizenAlreadyExists();
        }
        managersList.push_back(std::make_shared<Manager>(managerId, firstName, lastName, birthYear));
    }

    void City::addFaculty(int id, Skill skill, int addedPoints, Condition *pred) {
        for (const std::shared_ptr<Faculty<Condition>>& runFaculty:facultysList){
            if (runFaculty->getId() == id){
                throw FacultyAlreadyExists();
            }
        }
        facultysList.push_back(std::make_shared<Faculty<Condition>>(id, skill, addedPoints, pred));
    }//look! code duplication for all these functions

}


/**========================END City=========================================**/
