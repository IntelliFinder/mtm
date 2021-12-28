#include <iostream>

#include "citizen.h"
#include "skill.h"

namespace mtm {

    class Employee : public Citizen{
        double salary;
        double points;
        //skill set

    public:
        Employee(double salary, double points): salary(salary), points(points) {}
        ~Employee() = default;

    };
