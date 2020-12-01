#include <gamerules/Board.h>
#include <statemachine/StateMachine.h>
Board::Board(std::string name) {
    this->name;
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
    this->ssm = new StateMachine();
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

void Board::addPlayer(Player* playa) {
    this->players.push_back(playa);
}

BoardSpace* Board::getHead() const {
    return this->head;
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

StateMachine* Board::getSSM() {
    return ssm;
}

BoardSpace* Board::getTail() const {
    return tail;
}

BoardSpace* Board::findSpace(int spaceID) {
    BoardSpace* tmp = head;
    while (tmp != tail) {
        if (tmp->getSpaceID() == spaceID) {
            return tmp;
        }
        tmp = tmp->getNextSpace();
    }
    return nullptr;
}


BoardSpace* Board::findSpace(std::string name) {
    BoardSpace* tmp = head;
    while (tmp != tail) {
        if (tmp->getName() == name) {
            return tmp;
        }
        tmp = tmp->getNextSpace();
    }
    return nullptr;
}

Player* Board::getCurrentPlayer() {
    return currPlayer;
}

bool Board::checkForEndCond() {
    bool flag = false;
    if (players.size() < 2) {
        flag = true;
    }
    for (std::vector<Player*>::iterator it = players.begin(); it < players.end(); it++) {
        if ((*it)->getMoney() < 0) {
            flag = true;
        }
    }
    return flag;
}

bool Board::checkForStartCond() {
    return players.size() > 1;
}
 
std::vector<Player*> Board::getPlayers() const {
    return players;
}