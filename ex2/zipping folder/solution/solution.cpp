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
        }//I wanted to use getElementWithID but it's different
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
        Workplace* workplace = getElementWithId<Workplace>(workplacesList,workplaceId);
        if(!workplace) {
            throw WorkplaceDoesNotExist();
        }
        workplace->fireEmployee(employeeId,managerId);
        Citizen* employeeCitizen = getElementWithId<Citizen>(employeesList,employeeId);
        Employee* employee = dynamic_cast<Employee*>(employeeCitizen);
        employee->setSalary(-workplace->getWorkersSalary());
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
        aboveList.sort(compareById);//the right comparison
        for(const std::shared_ptr<Citizen>& citizen : aboveList){
            Citizen* cit = citizen.get();
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
