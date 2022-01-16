#ifndef WORKPLACE_H // include guard
#define WORKPLACE_H
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

namespace mtm {
    class Workplace {
    private:
        const int id;
        const std::string name;
        int workers_salary;
        int managers_salary;
        std::list<Manager *> managers_list;
        /**
         *
         * @param manager_id
         * @return true if the matching manager is hired
         */
        bool isManagerHired(const int manager_id) const;
        /**
         *
         * @param manager_id
         * @return the matching pointer, if doesn't exist, returns nullptr
         */
        Manager* getPointerToManager(const int manager_id);//I need * and not & for the list
    public:
        Workplace(int id, std::string name, int workersSalary, int managersSalary) : id(id), name(name),
                                                                                     workers_salary(workersSalary),
                                                                                     managers_salary(managersSalary),
                                                                                     managers_list(){};
        ~Workplace() = default;

        int getId() const;

        std::string getName() const;

        int getWorkersSalary() const;

        int getManagersSalary() const;

        template<class Condition>
        void hireEmployee(Condition condition, Employee *employee_add, int manager_id){
            if (!condition(employee_add)){
                throw EmployeeNotSelected();
            }
            if(!isManagerHired(manager_id)){
                throw ManagerIsNotHired();
            }
            Manager *trueManager = getPointerToManager(manager_id);
            employee_add->setSalary(workers_salary);
            return trueManager->addEmployee(employee_add);//will throw employeeIsNotHired if needed
        }

        void hireManager(Manager *manager_add);

        void fireEmployee(const int employee_id, const int manager_id);

        void fireManager(const int manager_id);
        /**
         *
         * @param employee_id
         * @return true if the matching employee exist in workplace
         */
        bool employeeExist( const int employee_id ) const;

        /**
         * prints name and groups(managers and their employees)
         * @param stream
         * @param workplace
         * @return ostream
         */
        friend std::ostream& operator<<(std::ostream& stream, const Workplace& workplace);



    };


}
#endif
