/*
Authors: Christopher Kennedy, Jackson Stanhope, Jim O'Donnell, Michael Zhou Lu, Ruben Quiros, and Shelby Crisp 
Class: ECE 4122
Last Date Modified: 12/1/20
Description:
This is the header file for the Player class. This class is used to identify the various players in the game 
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
class BoardSpace;
class Property;
class Board;

class Player {
    private:
    Board* board;   //Board pointer
    std::string name;   //Name of that player
    std::string addr;   //String for the player addr
    long money;         //Long for players money
    BoardSpace* boardSpace; // this is actually a pointer to a boardSpace Object.
    public:
    Player(std::string, Board*); //Constructor for the player class
    Player(std::string);    //Constructor for the player class
    Player();   //Default constructor
    void buy(Property*);    //Function to purchase property
    void sell(Property*);   //Function to sell property
    void addMoney(long);    //Function that adds money to that player
    void takeMoney(long);   //Function that takes money from a player
    void movePlayer(int); // moves it a certain number of spaces on the board
    void movePlayer(BoardSpace*); // moves a player directly to a space.
    long getMoney();    //Returns the amount of money that a player has
    std::string getAddr() const;    //String that returns the address of a given player
    void setAddr(std::string);  //Sets the address for a given player   
    BoardSpace* getSpace() const;   //gets the space that a given player is on
    std::string getName() const;    //Returns the name of the player
    void setName(std::string);  //Sets the name for a given player
};

#endif
