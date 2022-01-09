#include <iostream>
#include <list>

namespace mtm {

    class Manager : public Citizen{
        int salary;
        std::list<Employee*> employeesList;//list is good for erasing



    public:
        Manager(const unsigned int id, const std::string firstName, const std::string lastName, const int birthYear): Citizen(id,firstName,
                                                                                                                              lastName, birthYear),salary(0),
                                                                                                                              employeesList(),isHired(false){};
        Citizen* clone(){

            return new Manager(*this);
        }

        ~Manager() = default;

        int getSalary() const;
        void addEmployee(Employee *employeeToAdd);
        void removeEmployee(const int id);
        void setSalary(const int addSalary);
        void printShort(std::ostream &os) override;
        void printLong(std::ostream &os) override;

        bool isHired;//should be okay to be public , just in case for later: look! maybe should be private with methods



    };
}