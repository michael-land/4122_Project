/*
Authors: Christopher Kennedy, Jackson Stanhope, Jim O'Donnell, Michael Zhou Lu, Ruben Quiros, and Shelby Crisp 
Class: ECE 4122
Last Date Modified: 12/1/20
Description:
This is the header file for Statemachine 
*/

#include <statemachine/States.h>
#include <statemachine/Decision.h>
#include <gamerules/Player.h>

class Board;
class server;
struct playerMove;
struct playerMove;
#ifndef SSM_H
#define SSM_H

class StateMachine {
    private:
    server *serv;	//Holds a pointer to a server
    States state;	//Holds the current state
    Board* board;	//Holds a pointer to the board
    bool isClient;	//A bool that defines whether the statemachine is a client
    public:	
    StateMachine();	//Default constructor
    ~StateMachine();	//Default destructor
    States getCurrentState() const;	//Returns the current state 
    bool input(playerMove inMsg);	//Accepts an input and handles the message accordingly
    bool processBuy();	//Handles a buy
    bool processSell();	//Handles a sell
    bool processUpgrade();	//Processes an upgrade
    bool processRollDice(int numSpaces);	//Does the roll dice
    bool processEndTurn();	//Handles the end turn
    bool execOutputs(playerMove inMsg, bool flag);	//Handles a player move input message and executes them depending on the flag
	bool processJoin(playerMove);	//Handles when a new player joins
    void setIsClient(bool);	//Tells the statemachine whether it is a client or not
    server* getServer();	//Returns a pointer to the server
    void setServer(server*);	//Sets the server based on a pointer input
    

};

#endif
