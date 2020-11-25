#include <builder/BoardBuilder.h>

BoardBuilder::BoardBuilder() {
    this->numSpaces = 40;

    construct();
}

void BoardBuilder::construct() {
    Board* board = new Board("Technopoly");
    Property* prop;
    BoardSpace* boardSpace;
        
}