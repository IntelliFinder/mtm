#ifndef EXCPTIONS_H // include guard
#define EXCPTIONS_H
#include <iostream>
#include <set>

namespace mtm {

    class Exception: public std::exception{};

    //inheritors from Exception
    class CanNotLearnSkill:public Exception{};
    class SkillException: public Exception{};
    class EmpException: public Exception{};
    class ManagerException: public Exception{};
    class FacultyException: public Exception{};
    class CityException: public Exception{};

    //inheritors from SkillException
    class DidNotLearnSkill: public SkillException{};
    class SkillAlreadyLearned: public SkillException{};
    class NegativePoints: public SkillException{};

    //inheritors from EmpException
    class EmployeeAlreadyHired: public EmpException{};
    class EmployeeIsNotHired: public EmpException{};
    class EmployeeNotSelected: public EmpException{};

    //inheritors from ManagerException
    class ManagerIsNotHired: public ManagerException{};
    class ManagerAlreadyHired: public ManagerException{};
    class CanNotHireManager: public ManagerException{};

    //inheritors from FacultyException
    class EmployeeNotAccepted: public FacultyException{};

    //inheritors from CityException
    class CitizenAlreadyExists: public CityException{};
    class FacultyAlreadyExists: public CityException{};
    class WorkplaceAlreadyExists: public CityException{};
    class EmployeeDoesNotExist: public CityException{};
    class ManagerDoesNotExist: public CityException{};
    class WorkplaceDoesNotExist: public CityException{};
    class FacultyDoesNotExist: public CityException{};

}
#endif