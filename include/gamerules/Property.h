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
    Colors color;
    Player* owner;

    public:
    Property(std::string, long, long, Colors);
    long getRent() const;
    long getCost() const;
    void setRent(const long&);
    void setCost(const long&);
    std::string getName() const;
    void setName(const std::string&);
};

#endif