/*
Authors: Christopher Kennedy, Jackson Stanhope, Jim O'Donnell, Michael Zhou Lu, Ruben Quiros, and Shelby Crisp 
Class: ECE 4122
Last Date Modified: 12/1/20

Description:
This is the file that defines the functionality for the board class.
*/

#include <gamerules/Board.h>
#include <statemachine/StateMachine.h>

//Constructor for the board object that uses a string to define the boards name
Board::Board(std::string name)
{
    this->name;
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
    this->ssm = new StateMachine();
    this->ssm->setBoard(this);
}

//Function that adds a board space to the board object when passed a boardspace pointer.
void Board::addSpace(BoardSpace *boardSpace)
{
    if (!head)
    {
        this->head = boardSpace;
        this->tail = boardSpace;
        return;
    }
    BoardSpace *tmpPtr = this->tail;
    tail->setNextSpace(boardSpace);
    this->tail = boardSpace;
    this->tail->setPrevSpace(tmpPtr);
}

//Adds a player object to the board
void Board::addPlayer(Player *playa)
{
    this->players.push_back(playa);
}

//Returns the head of the board object
BoardSpace *Board::getHead() const
{
    return this->head;
}

//Destructor for the board object
Board::~Board()
{
    if (!head)
    {
        return;
    }
    BoardSpace *tmp = head;
    while (tmp->getNextSpace())
    {
        tmp = tmp->getNextSpace();
        delete tmp->getPrevSpace();
    }
    delete tmp;
    return;
}

//Returns a pointer to the state machine for the board
StateMachine *Board::getSSM()
{
    return ssm;
}

//Returns the tail boardspace for the board
BoardSpace *Board::getTail() const
{
    return tail;
}

//This function searches a board object for the spaces ID
BoardSpace *Board::findSpace(int spaceID)
{
    BoardSpace *tmp = head;
    while (tmp != tail)
    { //Loops through all of the spaces on the board until the space contains the specified ID
        if (tmp->getSpaceID() == spaceID)
        {
            return tmp;
        }
        tmp = tmp->getNextSpace();
    }
    return nullptr;
}

//Searches the board for the specified space name
BoardSpace *Board::findSpace(std::string name)
{
    BoardSpace *tmp = head;
    while (tmp != tail)
    {
        if (tmp->getName() == name)
        {
            return tmp;
        }
        tmp = tmp->getNextSpace();
    }
    return nullptr;
}

//Returns the current player
Player *Board::getCurrentPlayer()
{
    return currPlayer;
}

//Searches for the ending condition
bool Board::checkForEndCond()
{
    bool flag = false;
    if (players.size() < 2)
    {
        flag = true;
    }
    //Iterates through the vector returning true if the money is less than 0
    for (std::vector<Player *>::iterator it = players.begin(); it < players.end(); it++)
    {
        if ((*it)->getMoney() < 0)
        {
            flag = true;
        }
    }
    return flag;
}

//Returns the status of the start condition
bool Board::checkForStartCond()
{
    return players.size() > 1;
}

//Returns a pointer to the vector of players
std::vector<Player *> Board::getPlayers() const
{
    return players;
}

//Defines the current player bool with the passed player object
void Board::setCurrPlayer(Player *thisPlayer)
{
    this->currPlayer = thisPlayer;
}

//This switches who the current player is effectively changing the turn
void Board::swapCurrPlayer()
{
    if (currPlayer->getName() == players.at(0)->getName())
    {
        currPlayer = players.at(1);
    }
    else
    {
        currPlayer = players.at(0);
    }
}