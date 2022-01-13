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
Skill::Skill(const int id, const std::string name, int points) : id(id), name(name), points(points){}

Skill::Skill(const Skill &skill):id(skill.getId()),name(skill.getName()),points(skill.points) {}
Skill &Skill::operator=(const Skill &skill) {
    this->points = skill.getRequiredPoints();
    return *this;
}

int Skill::getId() const { return id; }

std::string Skill::getName() const { return name; }

int Skill::getRequiredPoints() const { return points; }
namespace mtm{
    Skill Skill::operator++(int ) {
        //Skill old(this->getId(), this->getName(), this->getRequiredPoints());
        Skill old(*this);
        points +=  1;
        return old;
    }

    Skill& Skill::operator+=(const int amount) {
        if (amount<0){
            throw NegativePoints();
        }
        points = points + amount;
        return *this;
    }
    /*Skill &Skill::operator+(int amount){
        if(amount<0){
            throw NegativePoints();
        }
        *this += amount;
        return *this;
    }*/
    Skill operator+(const Skill &sk1, int amount) {
        if(amount<0){
            throw NegativePoints();
        }
        return Skill(sk1.getId(),sk1.getName(),sk1.getRequiredPoints()+amount);
    }
    Skill operator+(int amount, const Skill &sk1) {
        return sk1 + amount;
    }


    std::ostream& operator<<(std::ostream &os, const Skill &sk) {
        os << sk.getName() << std::endl; // without << std::endl
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
namespace mtm {
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
bool Manager::isEmployeeSub( const int employeeId) const{
    for(const Employee* emp : employeesList){
        if( emp->getId()==employeeId ){
            return true;
        }
    }
    return false;
}
void Manager::addEmployee(Employee *employeeToAdd) {
    for (std::list<Employee*>::iterator employeeItr = employeesList.begin();employeeItr != employeesList.end(); employeeItr++) {
        if ((*employeeToAdd).getId() == (*employeeItr)->getId()){
            throw EmployeeAlreadyHired();
        }
        else if((*employeeToAdd).getId() < (*employeeItr)->getId()){
            employeesList.insert(employeeItr,employeeToAdd);
            return;
        }
    }
    //list is empty


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
            (*employeeItr)->setSalary(-salaryToMinus);
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
    //std::string birthYearStr = std::to_string(getBirthYear());
    std::string salaryStr = std::to_string(salary);
    os << getFirstName() + " " + getLastName()<<std::endl;
    //os << "id - " + idStr + " birth_year - " + birthYearStr<<std::endl;
    os << "Salary: " + salaryStr << std::endl; //look! code duplication, maybe we should create a function
}

void Manager::printLong(std::ostream &os) {
    std::string idStr = std::to_string(getId());
    std::string birthYearStr = std::to_string(getBirthYear());
    std::string salaryStr = std::to_string(salary);
    os << getFirstName() + " " + getLastName()<<std::endl;
    os << "id - " + idStr + " birth_year - " + birthYearStr<<std::endl;
    os << "Salary: " + salaryStr << std::endl; //look! code duplication, maybe we should create a function
    if(employeesList.size()) {
        os << "Employees: " << std::endl;
        /*for (std::reverse_iterator<std::list<Employee *>::iterator> employeeItr = employeesList.rbegin();
             employeeItr != employeesList.rend(); employeeItr++) {
            (*employeeItr)->printShort(os);
        }*/
        for (std::list<Employee*>::iterator employeeItr = employeesList.begin();employeeItr != employeesList.end(); employeeItr++) {
            (*employeeItr)->printShort(os);
        }
    }

}



/**========================END MANAGER=========================================**/

/**========================WORKPLACE===========================================**/
namespace mtm {
    bool Workplace::isManagerHired(const int managerId) const{
        for(Manager *runManager:managersList){
            if ((*runManager).getId() == managerId){
                return true;
            }
        }
        return false;
    }
    bool Workplace::employeeExist( const int empId ) const{
        for( const  Manager* manager: managersList){
            if( manager->isEmployeeSub(empId) ){
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
        if (managerAdd->isHired || managerAdd->getSalary()>0){
            throw CanNotHireManager();
        }
        managerAdd->isHired = true;
        managerAdd->setSalary(managersSalary);
        for (std::list<Manager*>::iterator managerItr = managersList.begin();managerItr != managersList.end(); managerItr++) {
            if((*managerAdd).getId() < (*managerItr)->getId()){
                managersList.insert(managerItr,managerAdd);
                return;
            }
        }//look! a bit code duplication
        managersList.push_back(managerAdd);
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
            os<< " Groups:"<< std::endl;
        }
        else{
            os<<std::endl;
        }
        for (Manager *pManager : workplace.managersList){
            os << "Manager ";
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
namespace mtm {

    bool City::isCitizenExist(const int id, const std::list <std::shared_ptr<Citizen>> &citizenList) {
        for (const std::shared_ptr <Citizen> &runCitizen: citizenList) {
            if (runCitizen->getId() == id) {
                return true;
            }
        }
        return false;
    }

    void City::addEmployee(const int employeeId, const std::string firstName, const std::string lastName,
                           const int birthYear) {
        if (isCitizenExist(employeeId, employeesList) || isCitizenExist(employeeId, managersList)) {
            throw CitizenAlreadyExists();
        }
        employeesList.push_back(std::make_shared<Employee>(employeeId, firstName, lastName, birthYear));
    }

    void City::addManager(const int managerId, const std::string firstName, const std::string lastName,
                          const int birthYear) {
        if (isCitizenExist(managerId, employeesList) || isCitizenExist(managerId, managersList)) {
            throw CitizenAlreadyExists();
        }
        managersList.push_back(std::make_shared<Manager>(managerId, firstName, lastName, birthYear));
    }

    void City::addFaculty(int id, Skill skill, int addedPoints, Condition *pred) {
        for (const std::shared_ptr <Faculty<Condition>> &runFaculty: facultysList) {
            if (runFaculty->getId() == id) {
                throw FacultyAlreadyExists();
            }
        }
        facultysList.push_back(std::make_shared<Faculty<Condition>>(id, skill, addedPoints, pred));
    }//look! code duplication for all these functions
    void City::createWorkplace(int id, std::string name, int workersSalary, int managersSalary) {
        for (const std::shared_ptr <Workplace> &runWorkplace: workplacesList) {
            if (runWorkplace->getId() == id) {
                throw WorkplaceAlreadyExists();
            }
        }
        workplacesList.push_back(std::make_shared<Workplace>(id, name, workersSalary, managersSalary));
    }

    void City::teachAtFaculty(const int employeeId, const int facultyId){
        if(!isCitizenExist(employeeId, employeesList)){
            throw EmployeeDoesNotExist();
        }
        /*
        Employee* employee= nullptr;
        for (const std::shared_ptr<Citizen>& runEmp:employeesList){
            if (runEmp->getId() == id){
                employee = dynamic_cast<Employee*>(runEmp.get());
            }
        }
        bool not_exists=true;
        for (const std::shared_ptr<Faculty<Condition>>& runFaculty:facultysList){//code duplication
            if (runFaculty->getId() == id){
                runFaculty->teach(employee);
                not_exists=false;
            }
        }
        if( not_exists ){
            throw FacultyDoesNotExist();
        }*/
        Citizen* employeeCitizen = getElementWithId<Citizen>(employeesList,employeeId);
        Employee* employee = dynamic_cast<Employee*>(employeeCitizen);
        Faculty<Condition>* pFaculty= getElementWithId<Faculty<Condition>>(facultysList,facultyId);
        if(pFaculty == nullptr){
            throw FacultyDoesNotExist();
        }
        pFaculty->teach(employee);
    }
    void City::hireManagerAtWorkplace(const int managerId, const int workplaceId) {
        if(!isCitizenExist( managerId, managersList)){
            throw ManagerDoesNotExist();
        }
        /*
        Manager* manager = nullptr;
        for(const std::shared_ptr<Citizen>& runManager: managersList){
            if( runManager->getId() == managerId ){
                manager = dynamic_cast<Manager*>(runManager.get());
            }
        }*/
        Citizen* managerCitizen = getElementWithId<Citizen>(managersList,managerId);
        Manager* manager = dynamic_cast<Manager*>(managerCitizen);
        bool workplace =false;
        for(const std::shared_ptr<Workplace>& runWork: workplacesList){
            if( runWork->getId() == workplaceId ){
                (runWork.get())->hireManager(manager);
                workplace = true;
            }
        }
        if(!workplace){
            throw WorkplaceDoesNotExist();
        }
    }


    void City::fireEmployeeAtWorkplace(const int employeeId, const int managerId, const int workplaceId){
        if(!isCitizenExist(employeeId,employeesList)){
            throw EmployeeDoesNotExist();
        }
        if(!isCitizenExist(managerId,managersList)){
            throw ManagerDoesNotExist();
        }
        //what if doesn't exist in workplace but yes in city? weird
        //bool workplace_exist =false;
        /*for(const std::shared_ptr<Workplace>& runWork: workplacesList){
            if( runWork->getId() == workplaceId ){
                runWork->fireEmployee(employeeId,managerId);
                workplace_exist = true;
            }
        }*/
        Workplace* workplace = getElementWithId<Workplace>(workplacesList,workplaceId);
        if(!workplace) {
            throw WorkplaceDoesNotExist();
        }
        workplace->fireEmployee(employeeId,managerId);
        Citizen* employeeCitizen = getElementWithId<Citizen>(employeesList,employeeId);
        Employee* employee = dynamic_cast<Employee*>(employeeCitizen);
        employee->setSalary(-workplace->getWorkersSalary());
        /*if(!workplace_exist){
            throw WorkplaceDoesNotExist();
        }*/
    }

    void City::fireManagerAtWorkplace(const int managerId, const int workplaceId){
        if(!isCitizenExist(managerId,managersList)){
            throw ManagerDoesNotExist();
        }
        Workplace* workplace = getElementWithId<Workplace>(workplacesList,workplaceId);
        if(!workplace) {
            throw WorkplaceDoesNotExist();
        }
        workplace->fireManager(managerId);
        Citizen* managerCitizen = getElementWithId<Citizen>(managersList,managerId);
        Manager* manager = dynamic_cast<Manager*>(managerCitizen);
        manager->setSalary(-workplace->getManagersSalary());
        for (const std::shared_ptr<Citizen>& runEmp:employeesList){
            if(manager->isEmployeeSub(runEmp->getId())){
                dynamic_cast<Employee*>(runEmp.get())->setSalary(-workplace->getWorkersSalary());
                manager->removeEmployee(runEmp->getId());
            }
        }
        //Workplace* workplace = nullptr;
        /*bool workplace_exist =false;
        for(const std::shared_ptr<Workplace>& runWork: workplacesList){
            if( runWork->getId() == workplaceId ){
                runWork->fireManager(managerId);
                workplace_exist = true;
            }
        }
        if(!workplace_exist){
            throw WorkplaceDoesNotExist();
        }*/
    }


    bool compareById(const std::shared_ptr<Citizen>& first, const std::shared_ptr<Citizen>& second){
        return first->getId()<second->getId();
    }


    int City::getAllAboveSalary(std::ostream &os, const int salary) const {
        std::list<std::shared_ptr<Citizen>> aboveList;
        for(const std::shared_ptr<Citizen>& emp : employeesList){
            if(dynamic_cast<Employee*>(emp.get())->getSalary()>=salary){
                aboveList.push_back(emp);
            }
        }
        for(const std::shared_ptr<Citizen>& man : managersList){
            if(dynamic_cast<Manager*>(man.get())->getSalary()>=salary){
                aboveList.push_back(man);
            }
        }
        // LOOK! this is comparison between pointers need to fix
        aboveList.sort(compareById);//default compare function of citizen
        for(const std::shared_ptr<Citizen>& citizen : aboveList){
            Citizen* cit = citizen.get();
            /*
            if( typeid( cit ) == typeid( Manager* ) ){
                dynamic_cast<Manager*>(cit)->printShort(os);
            } else if( typeid( cit ) == typeid( Employee* ) ){
                dynamic_cast<Employee*>( cit )->printShort(os);
            }*/
            cit->printShort(os);
        }
        return aboveList.size();
    }
    bool City::isWorkingInTheSameWorkplace(const int emp1Id, const int emp2Id){
        if(!isCitizenExist(emp1Id, employeesList) || !isCitizenExist(emp2Id, employeesList)){
            throw EmployeeDoesNotExist();
        }
        for( const std::shared_ptr<Workplace>& work : workplacesList ){
            if( work->employeeExist(emp1Id) && work->employeeExist(emp2Id) ){
                return true;
            }
        }
        return false;
    }
    void City::printAllEmployeesWithSkill(std::ostream &os, const int skillId) {
        std::list<std::shared_ptr<Citizen>> aboveList;
        for(const std::shared_ptr<Citizen>& emp : employeesList){
            if(dynamic_cast<Employee*>(emp.get())->hasSkill(skillId)){
                aboveList.push_back(emp);
            }
        }
        aboveList.sort(compareById);
        for(const std::shared_ptr<Citizen>& citizen : aboveList){
            Citizen* cit = citizen.get();
            cit->printShort(os);
        }
    }
}
/**========================END City=========================================**/
