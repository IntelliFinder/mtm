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

namespace mtm{

    Manager::Manager(const Manager& manager): Citizen(manager.getId(),manager.getFirstName(),manager.getLastName(),manager.getBirthYear())
            , salary(manager.getSalary()), employees_list(), is_hired(false){
        for (Employee* pRunEmployee:manager.employees_list) {
            employees_list.push_back(pRunEmployee);
        }
    }
    int Manager::getSalary() const {
        return this->salary;
    }
    bool Manager::isEmployeeSub( const int employee_id) const{
        for(const Employee* emp : employees_list){
            if(emp->getId() == employee_id ){
                return true;
            }
        }
        return false;
    }
    void Manager::addEmployee(Employee *employee_to_add) {
        for (std::list<Employee*>::iterator employeeItr = employees_list.begin(); employeeItr != employees_list.end(); employeeItr++) {
            if ((*employee_to_add).getId() == (*employeeItr)->getId()){
                throw EmployeeAlreadyHired();
            }
            else if((*employee_to_add).getId() < (*employeeItr)->getId()){
                employees_list.insert(employeeItr, employee_to_add);
                return;
            }
        }
        //list is empty
        employees_list.push_back(employee_to_add);
    }

    void Manager::removeEmployee(const int id) {
        for (std::list<Employee*>::iterator employeeItr = employees_list.begin(); employeeItr != employees_list.end(); employeeItr++) {
            if ((*employeeItr)->getId() == id){
                employees_list.erase(employeeItr);
                return;
            }
        }
        throw EmployeeIsNotHired();
    }
    void Manager::removeEmployeeAndSalary(const int id,int salary_to_minus) {//salary_to_minus>0
        for (std::list<Employee*>::iterator employeeItr = employees_list.begin(); employeeItr != employees_list.end(); employeeItr++) {
            if ((*employeeItr)->getId() == id){
                (*employeeItr)->setSalary(-salary_to_minus);
                employees_list.erase(employeeItr);
                return;
            }
        }
        throw EmployeeIsNotHired();
    }


    void Manager::setSalary(const int add_salary) {
        helpForSetInt(salary, add_salary);
    }

    void Manager::printShort(std::ostream &stream) {
        std::string id_str = std::to_string(getId());
        std::string salary_str = std::to_string(salary);
        stream << getFirstName() + " " + getLastName() << std::endl;
        stream << "Salary: " + salary_str << std::endl;
    }

    void Manager::printLong(std::ostream &stream) {
        std::string id_str = std::to_string(getId());
        std::string birth_year_str = std::to_string(getBirthYear());
        std::string salary_str = std::to_string(salary);
        stream << getFirstName() + " " + getLastName() << std::endl;
        stream << "id - " + id_str + " birth_year - " + birth_year_str << std::endl;
        stream << "Salary: " + salary_str << std::endl;
        if(!employees_list.empty()) {
            stream << "Employees: " << std::endl;
            for (std::list<Employee*>::iterator employeeItr = employees_list.begin(); employeeItr != employees_list.end(); employeeItr++) {
                (*employeeItr)->printShort(stream);
            }
        }

    }

}




