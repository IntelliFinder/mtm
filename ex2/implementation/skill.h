#include <iostream>

namespace mtm {

    class Skill {
        const unsigned int id;
        const std::string name;
        int points;
        double pro;
    public:
        Skill(const unsigned int id, const std::string name, int points) : id(id), name(name), points(points), pro(0.0) {}

        ~Skill() = default;

        unsigned int getId() const;

        std::string getName() const;

        int requiredPoints() const;

        Skill &operator++();

        Skill &operator+=(int amount);

        Skill &operator+(int amount);
        //or should it be friend to be able to do amount + Skill sk1





//print operators

//std operators

    friend bool operator>(const Skill sk1, const Skill sk2);

    friend bool operator<(const Skill sk1, const Skill sk2);

    friend bool operator!=(const Skill sk1, const Skill sk2);

    friend bool operator>=(const Skill sk1, const Skill sk2);

    friend bool operator<=(const Skill sk1, const Skill sk2);

    friend bool operator==(const Skill sk1, const Skill sk2);
     };

} //end namespace