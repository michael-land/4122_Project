#include <gamerules/BoardSpace.h>
#include <gamerules/Player.h>
#include <gamerules/Board.h>
#include <gamerules/Property.h>
using namespace std;

Player::Player(std::string name, Board *board)
{
    this->name = name;
    this->money = 1500;
    this->board = board;
    this->boardSpace = board->getHead();
}

Player::Player(string name)
{
    this->name;
    this->money = 1500;
    this->board = NULL;
    this->boardSpace = NULL;
}

Player::Player()
{
    this->name= "";
    this->money = 1500;
    this->board = NULL;
    this->boardSpace = NULL;
}

Player &Player::operator=(Player const &rhs) // copy assignment
{
    this->name = rhs.name;
    this->money = rhs.money;
    this-> board = rhs.board;
    this->boardSpace= rhs.boardSpace;
    return *this;
}


void Player::addMoney(long income)
{
    this->money += income;
}

void Player::takeMoney(long loss)
{
    this->money -= loss;
}

void Player::movePlayer(int numSpaces)
{
    BoardSpace *tmp;
    for (int i = 0; i < numSpaces; i++)
    {
        tmp = tmp->getNextSpace();
    }
    this->boardSpace = tmp;
}

void Player::movePlayer(BoardSpace *bs)
{
    this->boardSpace = bs;
}

void Player::buy(Property *prop)
{
    if (!prop->getOwner())
    {
        prop->setOwner(this);
    }
}

void Player::sell(Property *prop)
{
    if (prop->getOwner() == this)
    {
        prop->setOwner(nullptr);
    }
}

string Player::getName()
{
    return name;
}

void Player::setName(string name)
{
    name = name;
}

long Player::moneyCount()
{
    return money;
}