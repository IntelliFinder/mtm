
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
        std::list<std::shared_ptr<Citizen>> employeesList;
        std::list<std::shared_ptr<Citizen>> managersList;
        std::list<std::shared_ptr<Faculty<Condition>>> facultysList;//facultys and not ies for searching:)
        std::list<std::shared_ptr<Workplace>> workplacesList;
        bool isCitizenExist(const int id, const std::list<std::shared_ptr<Citizen>>& citizenList);

        //assume element exists
        template<class Element>
        Element* getElementWithId(std::list<std::shared_ptr<Element>> list, const int id){
            for (const std::shared_ptr<Element>& runElement:list){
                if(runElement->getId() == id){
                    return runElement.get();
                }
            }
            return nullptr;
        }

    public:
        explicit City(const std::string name):name(name),id(0),employeesList(),managersList(){}
        virtual ~City() = default;

        void addEmployee(const int employeeId, const std::string firstName, const std::string lastName, const int birthYear);
        //if employee already exist throw CitizenAlreadyExists
        void addManager(const int managerId, const std::string firstName, const std::string lastName, const int birthYear);
        //if manager already exist throw CitizenAlreadyExists
        void addFaculty(int id, Skill skill, int addedPoints, Condition* pred);
        //if faculty already exist throw FacultyAlreadyExists

        void createWorkplace(int id, std::string name, int workersSalary, int managersSalary);
        //throws WorkplaceAlreadyExists

        void teachAtFaculty(const int employeeId, const int facultyId);
        // throws FacultyDoesNotExist
        /**
         * throws:
         * 1.EmployeeDoesNotExist
         * 2.ManagerDoesNotExist
         * 3.WorkplaceDoesNotExist
         */
        template<class ConditionEmp>
        void hireEmployeeAtWorkplace(ConditionEmp condition, int employeeId, int managerId, int workPlaceId){
            if (!isCitizenExist(employeeId, employeesList)){
                throw EmployeeDoesNotExist();
            }
            if (!isCitizenExist(managerId, managersList)){
                throw ManagerDoesNotExist();
            }
            Workplace *runWorkplace=getElementWithId<Workplace>(workplacesList,workPlaceId);
            if(runWorkplace == nullptr){
                throw WorkplaceDoesNotExist();
            }
            Citizen* pCitizenAdd = getElementWithId<Citizen>(employeesList, employeeId);
            Employee *pEmployee = dynamic_cast<Employee *>(pCitizenAdd);
            int previousSalary = pEmployee->getSalary();
            runWorkplace->hireEmployee(condition,pEmployee,managerId);
            pEmployee->setSalary(previousSalary);
            return;

        }
        //look! generic functions for finding element in list will work way better
        /**
         * throws:
         * 1.ManagerDoesNotExist
         * 2.WorkplaceDoesNotExist
         */
        void hireManagerAtWorkplace(const int managerId,const int workplaceId);


        /**
         * throws:
         * 1.EmployeeDoesNotExist
         * 2.ManagerDoesNotExist
         * 3.WorkplaceDoesNotExist
         */
        void fireEmployeeAtWorkplace(const int employeeId, const int managerId, const int workplaceId);
        /**
         * throws:
         * 1.ManagerDoesNotExist
         * 2.WorkplaceDoesNotExist
         */
        void fireManagerAtWorkplace(const int managerId, const int workplaceId);

        /**
        prints short description to all citizens.salary>=salary
         print order by id (from small to big)
         return number of citizens that citizens.salary>=salary
         */
        int  getAllAboveSalary(std::ostream &os, const int salary) const;

        /**
         *throws EmployeeDoesNotExist
         */
        bool isWorkingInTheSameWorkplace(const int emp1Id, const int emp2Id);

        /**
         prints short
         */
        void printAllEmployeesWithSkill(std::ostream &os, const int skillId);
    };




}
#endif //CITY_H
