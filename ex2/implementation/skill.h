#include <iostream>
namespace mtm {

    class Skill {
        const unsigned int id;
        const std::string name;
        int points;
        double pro;
    public:
        Skill(const unsigned int id, const std::string name, int points, double pro) : id(id), name(name), points(points), pro(pro) {}

        ~Skill() = default;

        unsigned int getId() const;

        std::string getName() const;

        int requiredPoints() const;

        Skill &operator++();

        Skill &operator+=(int amount);


    };

//print operators

//std operators
    /*
    Skill operator>(const Skill sk1, const Skill sk2);

    Skill operator<(const Skill sk1, const Skill sk2);

    Skill operator!=(const Skill sk1, const Skill sk2);

    Skill operator>=(const Skill sk1, const Skill sk2);

    Skill operator<=(const Skill sk1, const Skill sk2);

    Skill operator==(const Skill sk1, const Skill sk2);
     */
} //end namespace