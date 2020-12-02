/*
Authors: Christopher Kennedy, Jackson Stanhope, Jim O'Donnell, Michael Zhou Lu, Ruben Quiros, and Shelby Crisp 
Class: ECE 4122
Last Date Modified: 12/1/20

Description:
This is the file that defines the functionality for the server State machine  class.
*/

#include <statemachine/ServerStateMachine.h>
#include <gamerules/Board.h>

//Constructor for the servers state machine
ServerStateMachine::ServerStateMachine()
{
    this->state = States::GAME_SETUP;
}

//Returns the state of the statemachine
States ServerStateMachine::getCurrentState() const
{
    return this->state;
}

//Returns whether or not there has been input recieved
bool ServerStateMachine::input(unsigned char in)
{
    switch (in)
    {
    case 'b':
    case 'B':
        return Decision::BUY; //Handles buy
        break;

    case 's':
    case 'S':
        return Decision::SELL; //Handles sell
        break;

    case 'r':
    case 'R':
        return Decision::ROLL_DICE; //Handles dice roll
        break;

    case 'h':
    case 'H':
        return Decision::UPGRADE; //Handles upgrade
        break;

    case 'n':
    case 'N':
        return Decision::END_TURN; //Handles end turn
        return;
    default:
        break;
    }
}

//Process whether a player attempted to buy something
bool ServerStateMachine::processBuy()
{
    Player *currPlayer = board->getCurrentPlayer();

    if (state == States::USER_INPUT)
    {
        if (currPlayer->getMoney() > currPlayer->get
    }
}
