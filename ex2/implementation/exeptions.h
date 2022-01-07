#include <iostream>
namespace mtm {

    class Exception: public std::exception {};
    class SkillException: public Exception{};
    class EmpException: public Exception{};
    class ManagerException: public Exception{};

    class DidNotLearnSkill: public SkillException{};
    class CanNotLearnSkill: public SkillException{};
    class SkillAlreadyLearned: public SkillException{};

    class EmployeeAlreadyHired: public EmpException{};
    class EmployeeIsNotHired: public EmpException{};
    class EmployeeNotSelected: public EmpException{};

    class ManagerIsNotHired: public ManagerException{};
    class ManagerAlreadyHired: public ManagerException{};
    class CanNotHireManager: public ManagerException{};
} //end namespace