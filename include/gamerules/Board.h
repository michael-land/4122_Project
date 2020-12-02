/*
Authors: Christopher Kennedy, Jackson Stanhope, Jim O'Donnell, Michael Zhou Lu, Ruben Quiros, and Shelby Crisp 
Class: ECE 4122
Last Date Modified: 12/1/20
Description:
This is the header file for the Board class. 
*/

#ifndef BOARD_H
#define BOARD_H

#include <gamerules/BoardSpace.h>
#include <gamerules/Player.h>
#include <vector>

class StateMachine;

class Board {
    private:
    std::string name;	//Name of the board
    BoardSpace* head;	//Pointer to the head of the board
    BoardSpace* tail;	//Pointer to the tail of the board	
    std::vector<Player*> players;	//Vector of players
    Player* currPlayer;	//Current player pointer
    long length;	//Length of the board
    StateMachine* ssm;	//Statemachine pointer for the board

    public:
    Board(std::string); //Default constructor
    void addSpace(BoardSpace*); //Add space func
    void addPlayer(Player*);	//Add player func to board
    int rollDice() const;	//rollDice to find the next position
    Player* getCurrentPlayer();	//Returns a pointer to the current player
    std::vector<Player*> getPlayers() const;	//Returns a vector of all of the players
    BoardSpace* getHead() const;	//Returns the head of the board
    StateMachine* getSSM();	//Returns a pointer to the statemachine
    BoardSpace* getTail() const;	//Returns a pointer to the tail of the board
    ~Board();	//Destructor
    BoardSpace* findSpace(int);	//Finds a specific space based on the int passed
    BoardSpace* findSpace(std::string);	//Finds a space based on a given string
    bool checkForStartCond();	//Checks for the given start coordinates
    bool checkForEndCond();	//Returns true of at the end position of the board
	void setCurrPlayer(Player* thisPlayer);	//Sets the current player for the board
    void swapCurrPlayer();	//Swaps the current player.
};

#endif
