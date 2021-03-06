/*
Authors: Christopher Kennedy, Jackson Stanhope, Jim O'Donnell, Michael Zhou Lu, Ruben Quiros, and Shelby Crisp 
Class: ECE 4122
Last Date Modified: 12/1/20

Description:
This is the header file for the Board factory class. It contains all of the contents of the BoardFactory class
*/

#include <gamerules/Board.h>
#include <gamerules/Property.h>

#ifndef BOARDFACTORY_H
#define BOARDFACTORY_H

class BoardFactory {
    private:
    Board* board;
    int numSpaces, maxSpaces;

    public:
    BoardFactory(Board*, int);
    BoardFactory& operator<<(std::string);
    void makeProperty(std::string, long); // makes an already existing boardSpace with a particular name into a property
    // sets the rent and cost.
    Board* makeBoard();
    Board* getBoard();
};

#endif
