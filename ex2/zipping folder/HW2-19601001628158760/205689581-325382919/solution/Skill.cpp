#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <set>

#include "exceptions.h"
#include "Skill.h"

namespace mtm{

    Skill::Skill(const int id, const std::string name, int points) : id(id), name(name), points(points){}

    Skill::Skill(const Skill &skill):id(skill.getId()),name(skill.getName()),points(skill.points) {}
    Skill &Skill::operator=(const Skill &skill) {
        this->points = skill.getRequiredPoints();
        return *this;
    }

    int Skill::getId() const { return id; }

    std::string Skill::getName() const { return name; }

    int Skill::getRequiredPoints() const { return points; }
    Skill Skill::operator++(int ) {
        Skill old(*this);
        points +=  1;
        return old;
    }

    Skill& Skill::operator+=(const int amount) {
        if (amount<0){
            throw NegativePoints();
        }
        points = points + amount;
        return *this;
    }
    Skill operator+(const Skill &skill_1, int amount) {
        if(amount<0){
            throw NegativePoints();
        }
        return Skill(skill_1.getId(),skill_1.getName(),skill_1.getRequiredPoints()+amount);
    }
    Skill operator+(int amount, const Skill &skill_1) {
        return skill_1 + amount;
    }


    std::ostream& operator<<(std::ostream &os, const Skill &skill) {
        os << skill.getName() << std::endl;
        return os;
    }

    /**==================friends=====================**/
    bool operator>(Skill const& skill_1, Skill const& skill_2){
        return skill_1.getId() > skill_2.getId();
    }

    bool operator<( mtm::Skill const& skill_1,  mtm::Skill const& skill_2){
        return skill_1.getId() < skill_2.getId();
    }

    bool operator==(Skill const& skill_1, Skill const& skill_2){
        return skill_1.getId() == skill_2.getId();
    }
    /**===================end friends================**/

    bool operator!=( Skill const& skill_1,  Skill const& skill_2){
        return !(skill_1 == skill_2);
    }

    bool operator>=( Skill const& skill_1,  Skill const& skill_2){
        return !(skill_1 < skill_2);
    }

    bool operator<=( Skill const& skill_1,  Skill const& skill_2){
        return !(skill_1 > skill_2);
    }




}




