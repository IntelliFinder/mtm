#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <set>

#include "exceptions.h"
#include "Skill.h"
#include "Citizen.h"
#include "Employee.h"
#include "Manager.h"
#include "Workplace.h"
#include "Faculty.h"
#include "City.h"

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
    bool City::isWorkingInTheSameWorkplace(const int employee1Id, const int employee2Id){
        if(!isCitizenExist(employee1Id, employeesList) || !isCitizenExist(employee2Id, employeesList)){
            throw EmployeeDoesNotExist();
        }
        for( const std::shared_ptr<Workplace>& work : workplacesList ){
            if( work->employeeExist(employee1Id) && work->employeeExist(employee2Id) ){
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