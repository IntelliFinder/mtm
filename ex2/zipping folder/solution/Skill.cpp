#include <iostream>
#include <memory>
#include <string>
#include <list>

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
    namespace mtm{
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
        Skill operator+(const Skill &sk1, int amount) {
            if(amount<0){
                throw NegativePoints();
            }
            return Skill(sk1.getId(),sk1.getName(),sk1.getRequiredPoints()+amount);
        }
        Skill operator+(int amount, const Skill &sk1) {
            return sk1 + amount;
        }


        std::ostream& operator<<(std::ostream &os, const Skill &sk) {
            os << sk.getName() << std::endl; // without << std::endl
            return os;
        }


        bool operator>( Skill const& sk1,  Skill const& sk2){
            return sk1.getId() > sk2.getId();
        }

        bool operator<( mtm::Skill const& sk1,  mtm::Skill const& sk2){
            return sk1.getId() < sk2.getId();
        }

        bool operator!=( Skill const& sk1,  Skill const& sk2){
            return sk1.getId() != sk2.getId();
        }

        bool operator>=( Skill const& sk1,  Skill const& sk2){
            return sk1.getId() >= sk2.getId();
        }

        bool operator<=( Skill const& sk1,  Skill const& sk2){
            return sk1.getId() <= sk2.getId();
        }

        bool operator==( Skill const& sk1,  Skill const& sk2){
            return sk1.getId() == sk2.getId();
        }
    }



}




