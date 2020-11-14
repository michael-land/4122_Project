#include <gamerules/BoardSpace.h>

BoardSpace::BoardSpace(std::string name, Property* property, Colors color) {
    this->property = property;
    this->name = name;
    this->color = color;
}

std::string BoardSpace::getName() const {
    return name;
}

void BoardSpace::setName(const std::string& name) {
    this-> name = name;
}

const Property* BoardSpace::getProperty() const {
    return property;
}

void BoardSpace::setProperty(Property* prop) {
    this->property = prop;
}

BoardSpace* BoardSpace::getNextSpace() const {
    return nextSpace;
}

BoardSpace* BoardSpace::getPrevSpace() const {
    return prevSpace;
}

void BoardSpace::setNextSpace(BoardSpace* nextSpace) {
    this->nextSpace = nextSpace;
}

void BoardSpace::setPrevSpace(BoardSpace* prevSpace) {
    this->prevSpace = prevSpace;
}

void BoardSpace::setColor(Colors color) {
    this->color = color;
}

Colors BoardSpace::getColor() {
    return color;
}

BoardSpace::~BoardSpace() {
    delete property;
}



