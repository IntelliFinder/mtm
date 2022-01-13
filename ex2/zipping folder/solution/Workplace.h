#ifndef WORKPLACE_H // include guard
#define WORKPLACE_H
#include <iostream>
#include <memory>
#include <string>
#include <list>

#include "exceptions.h"
#include "Skill.h"
#include "Citizen.h"
#include "Employee.h"
#include "Manager.h"

namespace mtm {
    class Workplace {
    private:
        const int id;
        const std::string name;
        int workersSalary;
        int managersSalary;
        std::list<Manager *> managersList;//list is good for erasing
        bool isManagerHired(const int managerId) const;
        Manager* getPointerToManager(const int managerId);//I need * and not & for the list
    public:
        Workplace(int id, std::string name, int workersSalary, int managersSalary) : id(id), name(name),
                                                                                workersSalary(workersSalary),
                                                                                managersSalary(managersSalary),
                                                                                managersList(){};
        ~Workplace() = default;

        int getId() const;

        std::string getName() const;

        int getWorkersSalary() const;

        int getManagersSalary() const;

        template<class Condition>
        void hireEmployee(Condition condition, Employee *employeeAdd, int managerId){
            if (!condition(employeeAdd)){
                throw EmployeeNotSelected();
            }
            if(!isManagerHired(managerId)){
                throw ManagerIsNotHired();
            }
            Manager *trueManager = getPointerToManager(managerId);
            employeeAdd->setSalary(-employeeAdd->getSalary());
            employeeAdd->setSalary(workersSalary);
            return trueManager->addEmployee(employeeAdd);//will throw employeeIsNotHired if needed
        }

        void hireManager(Manager *managerAdd);

        void fireEmployee(const int employeeId, const int managerId);

        void fireManager(const int managerId);

        bool employeeExist( const int empId ) const;

        friend std::ostream& operator<<(std::ostream& os, const Workplace& wp);



    };


}
#endif
