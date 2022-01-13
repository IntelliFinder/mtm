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
namespace mtm{

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
            for (std::list<Employee*>::iterator employeeItr = employeesList.begin();employeeItr != employeesList.end(); employeeItr++) {
                (*employeeItr)->printShort(os);
            }
        }

    }


}



