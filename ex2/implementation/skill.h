#include <iostream>
namespace mtm {

    class Skill {
        const unsigned int id;
        const std::string name;
        int points;
        double pro;
    public:
        Skill(const unsigned int id, const char *name, int points, double pro);

        int getId() const;

        std::string getName() const;

        int requiredPoints();

        Skill &operator++();

        Skill &operator+=(const int amount);

        Skill operator+(const int amount);
        //print operators

    };

//print operators

//std operators
    Skill operator>(const Skill sk1, const Skill sk2);

    Skill operator<(const Skill sk1, const Skill sk2);

    Skill operator!=(const Skill sk1, const Skill sk2);

    Skill operator>=(const Skill sk1, const Skill sk2);

    Skill operator<=(const Skill sk1, const Skill sk2);

    Skill operator==(const Skill sk1, const Skill sk2);
} //end namespace