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
        void removeEmployeeAndSalary(const int id,int salaryToMinus);//my function
        void setSalary(const int addSalary);
        void printShort(std::ostream &os) override;
        void printLong(std::ostream &os) override;

        bool isHired;//should be okay to be public , just in case for later: look! maybe should be private with methods
        bool isEmployeeSub( const int employeeId) const; //not in instructionss, added for city


    };
}
#endif