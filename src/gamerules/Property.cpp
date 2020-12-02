/*
Authors: Christopher Kennedy, Jackson Stanhope, Jim O'Donnell, Michael Zhou Lu, Ruben Quiros, and Shelby Crisp 
Class: ECE 4122
Last Date Modified: 12/1/20

Description:
This is the file that defines the functionality for the property class.
*/

#include <gamerules/Property.h>

//Constructor for the property object when passed a name and cost
Property::Property(std::string name, long cost) : BoardSpace(name)
{
    this->name = name;
    this->cost = cost;
    this->rent = 0.05 * cost;
}

//Returns the rent cost for a property
long Property::getRent() const
{
    return rent;
}

//Returns the cost for a property
long Property::getCost() const
{
    return cost;
}

//Defines the rent for a property
void Property::setRent(const long &newRent)
{
    this->rent = newRent;
}

//Defines the cost a given property
void Property::setCost(const long &newCost)
{
    this->cost = newCost;
}

//Returns the name of a property
std::string Property::getName() const
{
    return name;
}
//Defines the name for a property
void Property::setName(const std::string &newName)
{
    this->name = newName;
}

//Defines the owner of that property with a player argument
void Property::setOwner(Player *player)
{
    this->owner = player;
}

//Returns the owner of that property
Player *Property::getOwner() const
{
    return owner;
}

//Upgrades a property
void Property::upgrade()
{
    this->upgrades += 1;
}

//Returns the upgrade count on a property
int Property::getUpgrades() const
{
    return upgrades;
}

//Defines the number of upgrades a property has
void Property::setUpgrades(int up)
{
    this->upgrades = up;
}