#include <builder/BoardFactory.h>

BoardFactory::BoardFactory(Board* board, int maxSpaces) {
    this->board = board;
    this->maxSpaces = maxSpaces;
    this->numSpaces = 0;
}

BoardFactory& BoardFactory::operator<<(std::string spaceName) {
    int spaceID = numSpaces;
    BoardSpace* bs = new BoardSpace(spaceName);
    bs->setSpaceID(spaceID);
    board->addSpace(bs);
}

void BoardFactory::makeProperty(std::string propName, long cost) {
    BoardSpace* bs = board->findSpace(propName);
    Property* prop = new Property(propName, cost);
    delete bs;
    bs = prop;
}