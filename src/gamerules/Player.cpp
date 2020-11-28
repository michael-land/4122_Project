#include <gamerules/BoardSpace.h>
#include <gamerules/Player.h>
#include <gamerules/Board.h>
#include <gamerules/Property.h>
Player::Player(std::string name, Board* board) {
    this->name = name;
    this->money = 2000;
    this->board = board;
    this->boardSpace = board->getHead();
}

void Player::addMoney(long income) {
    this->money += income;
}

void Player::takeMoney(long loss) {
    this->money -= loss;
}

void Player::movePlayer(int numSpaces) {
    BoardSpace* tmp;
    for (int i = 0; i < numSpaces; i++) {
        tmp = tmp->getNextSpace();
    }
    this->boardSpace = tmp;
}

void Player::movePlayer(BoardSpace* bs) {
    this->boardSpace = bs;
}

void Player::buy(Property* prop) {
    if (!prop->getOwner()) {
        prop->setOwner(this);
    }
}

void Player::sell(Property* prop) {
    if (prop->getOwner() == this) {
        prop->setOwner(nullptr);
    }
}

long Player::getMoney() {
    return money;
}

BoardSpace* Player::getSpace() const {
    return boardSpace;
}