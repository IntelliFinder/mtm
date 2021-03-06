#ifndef MANAGER_H // include guard
#define MANAGER_H
#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <set>

#include "exceptions.h"
#include "Skill.h"
#include "Citizen.h"
#include "Employee.h"

namespace mtm {

    class Manager : public Citizen{
        int salary;
        std::list<Employee*> employeesList;//list is good for erasing



    public:
        Manager(const int id, const std::string firstName, const std::string lastName, const int birthYear): Citizen(id,firstName,
                                                                                                                             lastName, birthYear),salary(0),
                                                                                                                             employeesList(),isHired(false){};
        Manager(const Manager& manager);
        Manager* clone() override{//not sure about type here I think it should be Citizen*

            return new Manager(*this);
        }

        ~Manager() = default;

        int getSalary() const;
        void addEmployee(Employee *employeeToAdd);
        void removeEmployee(const int id);
        /**
         * removes employee and takes off <salaryToMinus> from his salary
         * @param id
         * @param salaryToMinus
         */
        void removeEmployeeAndSalary(const int id,int salaryToMinus);//my function
        void setSalary(const int addSalary);
        /**
         * prints <full name>
         * Salary: <Salary>
         * @param os
         */
        void printShort(std::ostream &os) override;
        /**
         * prints <full name>
         * id - <id> birth_year - <birth_year>
         * Salary: <Salary>
         * Employees:
         * <all employees>
         * @param os
         */
        void printLong(std::ostream &os) override;

        bool isHired;//bool variable that says if the manager is hired
        /**
         *
         * @param employeeId
         * @return true if the matching employee is in his list
         */
        bool isEmployeeSub( const int employeeId) const; //not in instructionss, added for city


    };
}
#endif