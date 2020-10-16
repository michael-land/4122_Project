#include <gamerules/Property.h>

Property::Property(std::string name, long cost, long rent) {
    this->name = name;
    this->cost = cost;
    this->rent = rent;
}

long Property::getRent() const {
    return rent;
}

long Property::getCost() const {
    return cost;
}

void Property::setRent(const long& newRent) {
    this->rent = newRent;
}

void Property::setCost(const long& newCost) {
    this->cost = newCost;
}

std::string Property::getName() const {
    return name;
}
void Property::setName(const std::string& newName) {
    this->name = newName;
}
