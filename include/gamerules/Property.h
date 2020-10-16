#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>

class Property {
    private:
    std::string name;
    long rent;
    long cost;

    public:
    long getRent() const;
    long getCost() const;
    void setRent(const long&);
    void setCost(const long&);
};

#endif