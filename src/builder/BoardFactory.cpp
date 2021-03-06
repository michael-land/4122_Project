/*
Authors: Christopher Kennedy, Jackson Stanhope, Jim O'Donnell, Michael Zhou Lu, Ruben Quiros, and Shelby Crisp 
Class: ECE 4122
Last Date Modified: 12/1/20

Description:
This is the file that defines the functionality for the BoardFactory class.
*/

#include <builder/BoardFactory.h>

//This is the default constructor for the board Factory Object
BoardFactory::BoardFactory(Board *board, int maxSpaces)
{
    this->board = board;
    this->maxSpaces = maxSpaces;
    this->numSpaces = 0;
}

//Operator Overload for the << stream to print out a board factory object
BoardFactory &BoardFactory::operator<<(std::string spaceName)
{
    int spaceID = numSpaces;
    BoardSpace *bs = new BoardSpace(spaceName);
    bs->setSpaceID(spaceID);
    board->addSpace(bs);
    return *this;
}

//Creates the property when provided a cost and property name
void BoardFactory::makeProperty(std::string propName, long cost)
{
    BoardSpace *bs = board->findSpace(propName);
    Property *prop = new Property(propName, cost);
    delete bs;
    bs = prop;
}

//Defines all of the different properties of the board using the names listed below
Board *BoardFactory::makeBoard()
{
    *this << "Go Jackets"
          << "Scheller College of Business"
          << "Buzz's Chest"
          << "Georgia Tech Research Institute"
          << "TUTION"
          << "Blue Route"
          << "North Avenue Apartments"
          << "Chance"
          << "The Varsity"
          << "MARTA"
          << "Academic Probation"
          << "East Village"
          << "Laundry"
          << "West Village"
          << "Woodruff"
          << "Red Route"
          << "Student Center"
          << "Buzz's Chest"
          << "Ferst Center for the Arts"
          << "Tech Green"
          << "Got an A on your test!"
          << "The CULC"
          << "Chance"
          << "Kendeda Building"
          << "Georgia Tech Library"
          << "Tech Express"
          << "College of Computing"
          << "Klaus Advanced Computing Building"
          << "Campus Dining"
          << "McCamish Pavilion"
          << "Go To Academic Probation"
          << "Van Leer"
          << "The Hive"
          << "Buzz's Chest"
          << "Russ Chandler Stadium"
          << "Tech Trolley"
          << "Chance"
          << "Tech Tower"
          << "School Fees"
          << "Bobby Dodd";

    this->makeProperty("Scheller College of Business", 400);
    this->makeProperty("Georgia Tech Research Institute", 400);
    this->makeProperty("North Avenue Apartments", 400);
    this->makeProperty("The Varsity", 400);
    this->makeProperty("MARTA", 400);
    this->makeProperty("East Village", 400);
    this->makeProperty("West Village", 400);
    this->makeProperty("Woodruff", 400);
    this->makeProperty("Student Center", 400);
    this->makeProperty("Ferst Center for the Arts", 400);
    this->makeProperty("Tech Green", 400);
    this->makeProperty("The CULC", 400);
    this->makeProperty("Kendeda Building", 400); // this looks painful
    this->makeProperty("Georgia Tech Library", 400);
    this->makeProperty("Tech Express", 400);
    this->makeProperty("College of Computing", 400);
    this->makeProperty("Klaus Advanced Computing Building", 400);
    this->makeProperty("McCamish Pavilion", 400);
    this->makeProperty("Van Leer", 400);
    this->makeProperty("The Hive", 400);
    this->makeProperty("Russ Chandler Stadium", 400);
    this->makeProperty("Tech Towner", 420);
    this->makeProperty("Bobby Dodd Stadium", 400);
    return board;
}

//Returns a pointer to the board.
Board *BoardFactory::getBoard()
{
    return this->board;
}