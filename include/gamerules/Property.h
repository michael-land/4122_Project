#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>

class Property {
    private:
    std::string name;
    long rent;
    long cost;

    public:
    Property(std::string, long, long);
    long getRent() const;
    long getCost() const;
    void setRent(const long&);
    void setCost(const long&);
    std::string getName() const;
    void setName(const std::string&);
};

#endif