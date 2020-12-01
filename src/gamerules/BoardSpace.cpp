#include <gamerules/BoardSpace.h>
#include <gamerules/Player.h>

BoardSpace::BoardSpace(std::string name) {
    this->name = name;
}

std::string BoardSpace::getName() const {
    return name;
}

void BoardSpace::setName(const std::string& name) {
    this-> name = name;
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

int BoardSpace::getSpaceID() const {
    return spaceID;
}

void BoardSpace::setSpaceID(const int& id) {
    spaceID = id;
}


BoardSpace::~BoardSpace() {

};

void BoardSpace::placeholder() {

};



