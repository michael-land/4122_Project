/*
Authors: Christopher Kennedy, Jackson Stanhope, Jim O'Donnell, Michael Zhou Lu, Ruben Quiros, and Shelby Crisp 
Class: ECE 4122
Last Date Modified: 12/1/20

Description:
This is the file that is used to implement the boardspace object.
*/

#include <gamerules/BoardSpace.h>
#include <gamerules/Player.h>

//This is the constructor for the board space
BoardSpace::BoardSpace(std::string name)
{
    this->name = name;
}

//This function returns the name for that board
std::string BoardSpace::getName() const
{
    return name;
}

//This function is passed a string that sets the name for that board space
void BoardSpace::setName(const std::string &name)
{
    this->name = name;
}

//Returns the next board space
BoardSpace *BoardSpace::getNextSpace() const
{
    return nextSpace;
}

//Returns the previous space from the current board space
BoardSpace *BoardSpace::getPrevSpace() const
{
    return prevSpace;
}

//Sets the next space with the boardspace pointer being passed
void BoardSpace::setNextSpace(BoardSpace *nextSpace)
{
    this->nextSpace = nextSpace;
}

//Sets the previous space with the board space pointer
void BoardSpace::setPrevSpace(BoardSpace *prevSpace)
{
    this->prevSpace = prevSpace;
}

//Returns the space ID for a given boardspace
int BoardSpace::getSpaceID() const
{
    return spaceID;
}

//Sets the space ID for a give Space
void BoardSpace::setSpaceID(const int &id)
{
    spaceID = id;
}

//Destructor for the boardspace object
BoardSpace::~BoardSpace(){

};

void BoardSpace::placeholder(){

};
