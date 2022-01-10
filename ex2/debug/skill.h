#include <iostream>
namespace mtm {

    class Skill {
        const int id;
        const std::string name;
        int points; //points needed to acquire skill
    public:
        Skill(const int id, const std::string name, int points);// : id(id), name(name), points(points) {}

        ~Skill() = default;

        int getId() const;

        std::string getName() const;

        int requiredPoints() const;

        Skill &operator++();

        Skill &operator+=(int amount);

        Skill &operator+(int amount);
        //or should it be friend to be able to do amount + Skill sk1




//print operators
        friend std::ostream& operator<<(std::ostream& os, const Skill& sk);
//std operators

        friend bool operator>( Skill const& sk1,  Skill const& sk2);
        friend bool operator<(mtm::Skill const&, mtm::Skill const&);
        //friend bool operator<( Skill const& sk1,  Skill const& sk2);

        friend bool operator!=( Skill const& sk1,  Skill const& sk2);

        friend bool operator>=( Skill const& sk1,  Skill const& sk2);

        friend bool operator<=( Skill const& sk1,  Skill const& sk2);

        friend bool operator==( Skill const& sk1,  Skill const& sk2);
     };

} //end namespace