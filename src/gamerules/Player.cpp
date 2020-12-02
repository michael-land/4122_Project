/*
Authors: Christopher Kennedy, Jackson Stanhope, Jim O'Donnell, Michael Zhou Lu, Ruben Quiros, and Shelby Crisp 
Class: ECE 4122
Last Date Modified: 12/1/20

Description:
This is the file that defines the functionality for the Player class.
*/

#include <gamerules/BoardSpace.h>
#include <gamerules/Player.h>
#include <gamerules/Board.h>
#include <gamerules/Property.h>

//Constructor for the player class which is passed a string name and a pointer to a board object
Player::Player(std::string name, Board *board)
{
    this->name = name;
    this->money = 1500;
    this->board = board;
    this->boardSpace = board->getHead();
}

//Adds the money to the player using a passed long income
void Player::addMoney(long income)
{
    this->money += income;
}

//Removes the passed amount of money from the player class
void Player::takeMoney(long loss)
{
    this->money -= loss;
}

//Moves the players position by numSpaces
void Player::movePlayer(int numSpaces)
{
    BoardSpace *tmp = this->boardSpace;
    for (int i = 0; i < numSpaces; i++)
    {
        tmp = tmp->getNextSpace();
    }
    this->boardSpace = tmp;
}

//Moves a player to a specific boardspace
void Player::movePlayer(BoardSpace *bs)
{
    this->boardSpace = bs;
}

//Buys a property for a give player if they do not already own it and if another player does not own it
void Player::buy(Property *prop)
{
    if (!prop->getOwner())
    {
        prop->setOwner(this);
        this->takeMoney(prop->getCost());
    }
}

//Sells whatever property that is passed to the function
void Player::sell(Property *prop)
{
    if (prop->getOwner() == this)
    {
        prop->setOwner(nullptr);
        this->addMoney(prop->getCost());
    }
}

//Returns the money long for that player
long Player::getMoney()
{
    return money;
}

//Returns the address for the player
std::string Player::getAddr() const
{
    return addr;
}

//Returns the space that a player is on
BoardSpace *Player::getSpace() const
{
    return boardSpace;
}

//Returns the name for that player
std::string Player::getName() const
{
    return name;
}

//Defines the name for a player
void Player::setName(std::string name)
{
    this->name = name;
}