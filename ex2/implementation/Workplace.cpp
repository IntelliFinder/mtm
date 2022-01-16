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

namespace mtm {
    bool Workplace::isManagerHired(const int managerId) const{
        for(Manager *runManager:managersList){
            if ((*runManager).getId() == managerId){
                return true;
            }
        }
        return false;
    }
    bool Workplace::employeeExist( const int employeeId ) const{
        for( const  Manager* manager: managersList){
            if( manager->isEmployeeSub(employeeId) ){
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
