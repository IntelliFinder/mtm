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
    bool Workplace::isManagerHired(const int manager_id) const{
        for(Manager *run_manager:managers_list){
            if ((*run_manager).getId() == manager_id){
                return true;
            }
        }
        return false;
    }
    bool Workplace::employeeExist( const int employee_id ) const{
        for( const  Manager* manager: managers_list){
            if( manager->isEmployeeSub(employee_id) ){
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
        return workers_salary;
    }

    int Workplace::getManagersSalary() const{
        return managers_salary;
    }

    void Workplace::hireManager(Manager *manager_add) {
        if(isManagerHired(manager_add->getId())){
            throw ManagerAlreadyHired();
        }
        if (manager_add->is_hired || manager_add->getSalary() > 0){
            throw CanNotHireManager();
        }
        manager_add->is_hired = true;
        manager_add->setSalary(managers_salary);
        for (std::list<Manager*>::iterator manager_iterator = managers_list.begin(); manager_iterator != managers_list.end(); manager_iterator++) {
            if((*manager_add).getId() < (*manager_iterator)->getId()){
                managers_list.insert(manager_iterator, manager_add);
                return;
            }
        }
        managers_list.push_back(manager_add);
    }

    void Workplace::fireEmployee(const int employee_id, const int manager_id) {
        if(!isManagerHired(manager_id)){
            throw ManagerIsNotHired();
        }
        Manager *manager = getPointerToManager(manager_id);
        manager->removeEmployeeAndSalary(employee_id, workers_salary);//should be positive
    }

    void Workplace::fireManager(const int manager_id) {
        if(!isManagerHired(manager_id)){
            throw ManagerIsNotHired();
        }
        Manager *manager = getPointerToManager(manager_id);
        manager->is_hired = false;
        manager->setSalary(-managers_salary);
        managers_list.remove(manager);

    }

    Manager *Workplace::getPointerToManager(const int manager_id) {
        for(Manager *manager_iterator:managers_list){
            if ((*manager_iterator).getId() == manager_id){
                return manager_iterator;
            }
        }
        return nullptr;
    }
    std::ostream &operator<<(std::ostream &stream, const Workplace &workplace) {
        stream << "Workplace name - " << workplace.name;
        if (!workplace.managers_list.empty()){
            stream << " Groups:" << std::endl;
        }
        else{
            stream << std::endl;
        }
        for (Manager *ptr_manager : workplace.managers_list){
            stream << "Manager ";
            ptr_manager->printLong(stream);
        }
        //endl here doesn't seem right because short print does it for us
        return stream;
    }




}
