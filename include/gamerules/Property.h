/*
Authors: Christopher Kennedy, Jackson Stanhope, Jim O'Donnell, Michael Zhou Lu, Ruben Quiros, and Shelby Crisp 
Class: ECE 4122
Last Date Modified: 12/1/20
Description:
This is the header file for the Property class. This class is used to define the various property pieces.
*/

#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include <gamerules/Board.h>
#include <render/Colors.h>

class Property : public BoardSpace {
    private:
    std::string name;   //Name of the property
    long rent;  //The cost of rent for the space
    long cost;  //Cost of buying that property type
    Player* owner;  //A player pointer to the owner of that property
    int upgrades; // 0 is nothing, 1 - 4 is a house, 5 is a hotel.

    public:
    Property(std::string, long);    //Default constructor
    long getRent() const;   //Returns the rent for that property type
    long getCost() const;   //Returns the cost for buying that property
    void setRent(const long&);  //Sets the rent for the property
    void setCost(const long&);  //Sets the cost for that property
    std::string getName() const;    //Returns the name of that property
    void setName(const std::string&);   //Sets the name for that property
    void setOwner(Player*); //Sets the owner for that property
    Player* getOwner() const;   //Returns the owner for that property
    void upgrade(); //Upgrades that property
    int getUpgrades() const;    //Returns the status of that property
    void setUpgrades(int);  //Defines the number of upgrades to that property
};

#endif
