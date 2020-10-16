#include <gamerules/Board.h>

Board::Board(std::string name) {
    this->name;
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}

void Board::addSpace(BoardSpace* boardSpace) {
    if (!head) {
        this->head = boardSpace;
        this->tail = boardSpace;
        return;
    }
    BoardSpace* tmpPtr = this->tail;
    tail->setNextSpace(boardSpace);
    this->tail = boardSpace;
    this->tail->setPrevSpace(tmpPtr);
}

Board& Board::operator<<(BoardSpace* boardSpace) {
    addSpace(boardSpace);
    return *this;
}

void Board::addPlayer(Player* playa) {
    this->players.push_back(playa);
}

Board::~Board() {
    if(!head) {
        return;
    }
    BoardSpace* tmp = head;
    while (tmp->getNextSpace()) {
        tmp = tmp->getNextSpace();
        delete tmp->getPrevSpace();
    }
    delete tmp;
    return;
}
