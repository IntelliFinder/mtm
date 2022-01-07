#include <iostream>
namespace mtm {

    class Exception:std::exception {

    public:
        class DidNotLearnSkill:Exception{};//not sure how to do it
        class CanNotLearnSkill{};
        class SkillAlreadyLearned{};
        class EmployeeAlreadyHired{};
        class EmployeeIsNotHired{};
        class EmployeeNotSelected{};
        class ManagerIsNotHired:mtm::Exception{};
        class ManagerAlreadyHired{};
        class CanNotHireManager{};
    };
} //end namespace