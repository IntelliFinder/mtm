
#ifndef CITY_H
#define CITY_H
#include <iostream>
class Condition{
public:
    virtual bool operator()(mtm::Employee* employee)=0;
};
namespace mtm {
    class City{
        const std::string name;
        std::list<Employee*> empList;
        std::list<Manager*> mgrList;
        std::list<Faculty*> facultyList;
        std::list<Workplace*> workList;
    public:
        City(const std::string name):name(name),id(0){}
        virtual ~City() = default;

        void addEmployee(const int id, const std::string firstName, const std::string lastName, const int birthYear);
        //if employee already exist throw CitizenAlreadyExists
        void addManager(const int id, const std::string firstName, const std::string lastName, const int birthYear);
        //if manager already exist throw CitizenAlreadyExists
        void addFaculty(int id, Skill skill, int addedPoints, Condition* pred);
        //if faculty already exist throw FacultyAlreadyExists


        /**
         * throws:
         * 1.EmployeeDoesNotExist
         * 2.ManagerDoesNotExist
         * 3.WorkplaceDoesNotExist
         */
        template<class ConditionEmp>
        void hireEmployeeAtWorkplace(ConditionEmp condition, Employee *employeeAdd, int managerId, int facultyId){

        }

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
