
#ifndef CITY_H
#define CITY_H
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

namespace mtm {
    class City{
        const std::string name;
        int id;
        std::list<std::shared_ptr<Citizen>> employees_list;
        std::list<std::shared_ptr<Citizen>> managers_list;
        std::list<std::shared_ptr<Faculty<Condition>>> facultys_list;
        std::list<std::shared_ptr<Workplace>> workplaces_list;
        bool isCitizenExist(const int id, const std::list<std::shared_ptr<Citizen>>& citizen_list);

        //assume element exists
        template<class Element>
        Element* getElementWithId(std::list<std::shared_ptr<Element>> list, const int id){
            for (const std::shared_ptr<Element>& run_element:list){
                if(run_element->getId() == id){
                    return run_element.get();
                }
            }
            return nullptr;
        }

    public:
        explicit City(const std::string name): name(name), id(0), employees_list(), managers_list(){}
        virtual ~City() = default;

        void addEmployee(const int employee_id, const std::string first_name, const std::string last_name, const int birth_year);
        //if employee already exist throw CitizenAlreadyExists
        void addManager(const int manager_id, const std::string first_name, const std::string last_name, const int birth_year);
        //if manager already exist throw CitizenAlreadyExists
        void addFaculty(int id, Skill skill, int added_points, Condition* predicate);
        //if faculty already exist throw FacultyAlreadyExists

        void createWorkplace(int id, std::string name, int workers_salary, int managers_salary);
        //throws WorkplaceAlreadyExists

        void teachAtFaculty(const int employee_id, const int faculty_id);
        // throws FacultyDoesNotExist
        /**
         * throws:
         * 1.EmployeeDoesNotExist
         * 2.ManagerDoesNotExist
         * 3.WorkplaceDoesNotExist
         */
        template<class ConditionEmp>
        void hireEmployeeAtWorkplace(ConditionEmp condition, int employee_id, int manager_id, int workplace_id){
            if (!isCitizenExist(employee_id, employees_list)){
                throw EmployeeDoesNotExist();
            }
            if (!isCitizenExist(manager_id, managers_list)){
                throw ManagerDoesNotExist();
            }
            Workplace *ptr_workplace=getElementWithId<Workplace>(workplaces_list, workplace_id);
            if(ptr_workplace == nullptr){
                throw WorkplaceDoesNotExist();
            }
            Citizen* ptr_citizen_add = getElementWithId<Citizen>(employees_list, employee_id);
            Employee *ptr_employee = dynamic_cast<Employee *>(ptr_citizen_add);
            ptr_workplace->hireEmployee(condition, ptr_employee, manager_id);
            return;

        }
        //look! generic functions for finding element in list will work way better
        /**
         * throws:
         * 1.ManagerDoesNotExist
         * 2.WorkplaceDoesNotExist
         */
        void hireManagerAtWorkplace(const int manager_id, const int workplace_id);


        /**
         * throws:
         * 1.EmployeeDoesNotExist
         * 2.ManagerDoesNotExist
         * 3.WorkplaceDoesNotExist
         */
        void fireEmployeeAtWorkplace(const int employee_id, const int manager_id, const int workplace_id);
        /**
         * throws:
         * 1.ManagerDoesNotExist
         * 2.WorkplaceDoesNotExist
         */
        void fireManagerAtWorkplace(const int manager_id, const int workplace_id);

        /**
        prints short description to all citizens.salary>=salary
         print order is by worker's id (from small to big)
         return number of workers(employee/manager) that worker.salary>=salary
         */
        int  getAllAboveSalary(std::ostream &stream, const int salary) const;

         /**
          * (if needed,)throws EmployeeDoesNotExist
          * @param employee_id_1
          * @param employee_id_2
          * @return true if the two matching employees are WorkingInTheSameWorkplace
          */
        bool isWorkingInTheSameWorkplace(const int employee_id_1, const int employee_id_2);

        /**
         prints short for all EmployeesWithSkill, sorted by id
         */
        void printAllEmployeesWithSkill(std::ostream &stream, const int skill_id);
    };




}
#endif //CITY_H
