#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include <gamerules/Board.h>
#include <render/Colors.h>

class Property : public BoardSpace {
    private:
    std::string name;
    long rent;
    long cost;
    Player* owner;
    int upgrades; // 0 is nothing, 1 - 4 is a house, 5 is a hotel.

    public:
    Property(std::string, long, long);
    long getRent() const;
    long getCost() const;
    void setRent(const long&);
    void setCost(const long&);
    std::string getName() const;
    void setName(const std::string&);
    void setOwner(Player*);
    Player* getOwner() const;
    void upgrade();
    int getUpgrades() const;
    void setUpgrades(int);
};

#endif