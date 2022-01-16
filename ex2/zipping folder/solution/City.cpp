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

    bool City::isCitizenExist(const int id, const std::list <std::shared_ptr<Citizen>> &citizen_list) {
        for (const std::shared_ptr <Citizen> &runCitizen: citizen_list) {
            if (runCitizen->getId() == id) {
                return true;
            }
        }
        return false;
    }

    void City::addEmployee(const int employee_id, const std::string first_name, const std::string last_name,
                           const int birth_year) {
        if (isCitizenExist(employee_id, employees_list) || isCitizenExist(employee_id, managers_list)) {
            throw CitizenAlreadyExists();
        }
        employees_list.push_back(std::make_shared<Employee>(employee_id, first_name, last_name, birth_year));
    }

    void City::addManager(const int manager_id, const std::string first_name, const std::string last_name,
                          const int birth_year) {
        if (isCitizenExist(manager_id, employees_list) || isCitizenExist(manager_id, managers_list)) {
            throw CitizenAlreadyExists();
        }
        managers_list.push_back(std::make_shared<Manager>(manager_id, first_name, last_name, birth_year));
    }

    void City::addFaculty(int id, Skill skill, int added_points, Condition *predicate) {
        for (const std::shared_ptr <Faculty<Condition>> &runFaculty: facultys_list) {
            if (runFaculty->getId() == id) {
                throw FacultyAlreadyExists();
            }
        }//I wanted to use getElementWithID but it's different
        facultys_list.push_back(std::make_shared<Faculty<Condition>>(id, skill, added_points, predicate));
    }//look! code duplication for all these functions
    void City::createWorkplace(int id, std::string name, int workers_salary, int managers_salary) {
        for (const std::shared_ptr <Workplace> &runWorkplace: workplaces_list) {
            if (runWorkplace->getId() == id) {
                throw WorkplaceAlreadyExists();
            }
        }
        workplaces_list.push_back(std::make_shared<Workplace>(id, name, workers_salary, managers_salary));
    }

    void City::teachAtFaculty(const int employee_id, const int faculty_id){
        if(!isCitizenExist(employee_id, employees_list)){
            throw EmployeeDoesNotExist();
        }
        Citizen* employeeCitizen = getElementWithId<Citizen>(employees_list, employee_id);
        Employee* employee = dynamic_cast<Employee*>(employeeCitizen);
        Faculty<Condition>* pFaculty= getElementWithId<Faculty<Condition>>(facultys_list, faculty_id);
        if(pFaculty == nullptr){
            throw FacultyDoesNotExist();
        }
        pFaculty->teach(employee);
    }
    void City::hireManagerAtWorkplace(const int manager_id, const int workplace_id) {
        if(!isCitizenExist(manager_id, managers_list)){
            throw ManagerDoesNotExist();
        }
        Citizen* managerCitizen = getElementWithId<Citizen>(managers_list, manager_id);
        Manager* manager = dynamic_cast<Manager*>(managerCitizen);
        bool workplace =false;
        for(const std::shared_ptr<Workplace>& runWork: workplaces_list){
            if(runWork->getId() == workplace_id ){
                (runWork.get())->hireManager(manager);
                workplace = true;
            }
        }
        if(!workplace){
            throw WorkplaceDoesNotExist();
        }
    }


    void City::fireEmployeeAtWorkplace(const int employee_id, const int manager_id, const int workplace_id){
        if(!isCitizenExist(employee_id, employees_list)){
            throw EmployeeDoesNotExist();
        }
        if(!isCitizenExist(manager_id, managers_list)){
            throw ManagerDoesNotExist();
        }
        //what if doesn't exist in workplace but yes in city? weird
        Workplace* workplace = getElementWithId<Workplace>(workplaces_list, workplace_id);
        if(workplace == nullptr) {
            throw WorkplaceDoesNotExist();
        }
        workplace->fireEmployee(employee_id, manager_id);
        Citizen* employeeCitizen = getElementWithId<Citizen>(employees_list, employee_id);
        Employee* employee = dynamic_cast<Employee*>(employeeCitizen);
        employee->setSalary(-workplace->getWorkersSalary());
    }

    void City::fireManagerAtWorkplace(const int manager_id, const int workplace_id){
        if(!isCitizenExist(manager_id, managers_list)){
            throw ManagerDoesNotExist();
        }
        Workplace* workplace = getElementWithId<Workplace>(workplaces_list, workplace_id);
        if(workplace == nullptr) {
            throw WorkplaceDoesNotExist();
        }
        workplace->fireManager(manager_id);
        Citizen* managerCitizen = getElementWithId<Citizen>(managers_list, manager_id);
        Manager* manager = dynamic_cast<Manager*>(managerCitizen);
        manager->setSalary(-workplace->getManagersSalary());
        for (const std::shared_ptr<Citizen>& runEmp:employees_list){
            if(manager->isEmployeeSub(runEmp->getId())){
                manager->removeEmployee(runEmp->getId());
            }
        }
    }


    bool compareById(const std::shared_ptr<Citizen>& first, const std::shared_ptr<Citizen>& second){
        return first->getId()<second->getId();
    }


    int City::getAllAboveSalary(std::ostream &stream, const int salary) const {
        std::list<std::shared_ptr<Citizen>> aboveList;
        for(const std::shared_ptr<Citizen>& emp : employees_list){
            if(dynamic_cast<Employee*>(emp.get())->getSalary()>=salary){
                aboveList.push_back(emp);
            }
        }
        for(const std::shared_ptr<Citizen>& man : managers_list){
            if(dynamic_cast<Manager*>(man.get())->getSalary()>=salary){
                aboveList.push_back(man);
            }
        }
        aboveList.sort(compareById);//the right comparison
        for(const std::shared_ptr<Citizen>& citizen : aboveList){
            Citizen* cit = citizen.get();
            cit->printShort(stream);
        }
        return aboveList.size();
    }
    bool City::isWorkingInTheSameWorkplace(const int employee_id_1, const int employee_id_2){
        if(!isCitizenExist(employee_id_1, employees_list) || !isCitizenExist(employee_id_2, employees_list)){
            throw EmployeeDoesNotExist();
        }
        for( const std::shared_ptr<Workplace>& work : workplaces_list ){
            if(work->employeeExist(employee_id_1) && work->employeeExist(employee_id_2) ){
                return true;
            }
        }
        return false;
    }
    void City::printAllEmployeesWithSkill(std::ostream &stream, const int skill_id) {
        std::list<std::shared_ptr<Citizen>> aboveList;
        for(const std::shared_ptr<Citizen>& emp : employees_list){
            if(dynamic_cast<Employee*>(emp.get())->hasSkill(skill_id)){
                aboveList.push_back(emp);
            }
        }
        aboveList.sort(compareById);
        for(const std::shared_ptr<Citizen>& citizen : aboveList){
            Citizen* cit = citizen.get();
            cit->printShort(stream);
        }
    }
}