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
        std::list<Employee*> employees_list;//list is good for erasing



    public:
        Manager(const int id, const std::string first_name, const std::string last_name, const int birth_year): Citizen(id, first_name,
                                                                                                                        last_name, birth_year), salary(0),
                                                                                                                employees_list(), is_hired(false){};
        Manager(const Manager& manager);
        Manager* clone() override{

            return new Manager(*this);
        }

        ~Manager() = default;

        int getSalary() const;
        /**
         * addEmployee: adds employee to list<Employee*> of manager
         * @param employee_to_add
         */
        void addEmployee(Employee *employee_to_add);
        void removeEmployee(const int id);
        /**
         * removeEmployeeAndSalary: removes employee and takes off <salary_to_minus> from his salary
         * @param id
         * @param salary_to_minus
         */
        void removeEmployeeAndSalary(const int id,int salary_to_minus);
        void setSalary(const int add_salary);
        /**
         * prints <full name>
         * Salary: <Salary>
         * @param stream - stream to output
         */
        void printShort(std::ostream &stream) override;
        /**
         * prints <full name>
         * id - <id> birth_year - <birth_year>
         * Salary: <Salary>
         * Employees:
         * <all employees>
         * @param stream
         */
        void printLong(std::ostream &stream) override;

        /** is Hireed: bool variable that says if the manager is hired**/
        bool is_hired;
        /**
         * isEmployeeSun: functions checks whether an employee is subordinate of manager
         * @param employee_id
         * @return true if the matching employee is in his list
         */
        bool isEmployeeSub( const int employee_id) const;


    };
}
#endif