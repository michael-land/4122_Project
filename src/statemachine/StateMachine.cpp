/*
Authors: Christopher Kennedy, Jackson Stanhope, Jim O'Donnell, Michael Zhou Lu, Ruben Quiros, and Shelby Crisp 
Class: ECE 4122
Last Date Modified: 12/1/20

Description:
This is the file that defines the functionality for the basic state machine class.
*/

#include <statemachine/StateMachine.h>
#include <gamerules/Board.h>
#include <gamerules/Property.h>
#include <multiplayer/MultiplayerObjects.h>
#include <GL/glut.h>
#include <iostream>

//Default constructor for the statemachine
StateMachine::StateMachine()
{
    this->state = States::GAME_SETUP;
}

//Returns the current state of the state machine
States StateMachine::getCurrentState() const
{
    return this->state;
}

//Sets the statemachine to handle a client
void StateMachine::setIsClient(bool isClient)
{
    this->isClient = isClient;
}

//Handles input and returns false if it fails to handle an input message
bool StateMachine::input(playerMove inMsg)
{ // pass message in here
    bool flag;
    std::cout << "inputs" << std::endl;
    switch (inMsg.moveType)
    {
    case 'b':
    case 'B':
        flag = processBuy();
        break;

    case 's':
    case 'S':
        flag = processSell();
        break;

    case 'r':
    case 'R':
        flag = processRollDice(inMsg.playerRoll);
        break;

    case 'h':
    case 'H':
        flag = processUpgrade();
        break;

    case 'n':
    case 'N':
        flag = processEndTurn();
        break;

    case 'j':
    case 'J':
        flag = processJoin(inMsg);
        break;

    default:
        flag = false;
        break;
    }
    execOutputs(inMsg, flag);

    return flag;
}

//Returns whether a buy or sell is possible
bool StateMachine::processBuy()
{
    Player *currPlayer = board->getCurrentPlayer();
    BoardSpace *space = currPlayer->getSpace();
    Property *prop;
    if (state == States::USER_INPUT)
    {
        prop = dynamic_cast<Property *>(space);
        if (!prop)
        {
            return false;
        }
        if (currPlayer->getMoney() > prop->getCost())
        {
            currPlayer->buy(prop);
            state = States::UPDATE_BOARD;
            return true;
        }
    }
    return false;
}

//Returns true if the sell is possible else it returns false
bool StateMachine::processSell()
{
    Player *currPlayer = board->getCurrentPlayer();
    BoardSpace *space = currPlayer->getSpace();
    Property *prop;
    if (state == States::USER_INPUT)
    {
        prop = dynamic_cast<Property *>(space);
        if (!prop)
        {
            return false;
        }
        if (prop->getOwner() == currPlayer)
        {
            currPlayer->sell(prop);
            state = States::UPDATE_BOARD;
            return true;
        }
    }
    return false;
}

//If the state does not allow the user to roll dice return false else return true
bool StateMachine::processRollDice(int numSpaces)
{
    if (state != States::USER_INPUT)
    {
        return false;
    }
    if (numSpaces > 12)
    {
        return false;
    }
    Player *currPlayer = board->getCurrentPlayer();
    currPlayer->movePlayer(numSpaces);
    state = States::UPDATE_BOARD;
    return true;
}
//Handles the end of a turn
bool StateMachine::processEndTurn()
{
    this->board->swapCurrPlayer(); // swap current player to other player in vector
    return true;
}

//Processes a player join action. It allows clients to join the game
bool StateMachine::processJoin(playerMove inMsg)
{ // a join is represented by the "J" character, although that isn't necessarily a keyboard option.
    if (state != States::GAME_SETUP) return false;
    // std::cout << "Player Joining!" << std::endl;
    if (state != States::GAME_SETUP)
    {
        return false;
    }

    auto playerVec = board->getPlayers();
    // std::cout << "got players" << std::endl;
    // std::string str(inMsg.playerID);
    bool exists;
    if (playerVec.size() != 0)
    {
        for (std::vector<Player *>::iterator it = playerVec.begin(); it < playerVec.end(); it++)
        {
            if ((*it)->getName() == inMsg.playerID)
            {
                exists = true;
            }
            else
            {
                exists = false;
            }
        }
    }
    else
    {
        exists = false;
    }
    if (!exists)
    {
        // std::cout << "new player sent a message" << std::endl;
        Player *newPlayer = new Player(inMsg.playerID, this->board);
        this->board->addPlayer(newPlayer);
        if (!isClient) {
            // std::cout << "push back msgs" << std::endl;
		    serv->joinedPlayersMsg.push_back(inMsg);
        }
		// std::cout << "player joined the battle" << std::endl;
		if (playerVec.size() == 1)
        {
            board->setCurrPlayer(newPlayer);
        }
        return true;
    }
    return false;
}

// Handles the upgrade of a property
bool StateMachine::processUpgrade()
{
    if (state != States::USER_INPUT)
    {
        return false;
    }
    Player *currPlayer = board->getCurrentPlayer();
    BoardSpace *space = currPlayer->getSpace();
    Property *prop = dynamic_cast<Property *>(space);
    if (!prop)
    {
        return false;
    }
    if (prop->getOwner() == currPlayer && currPlayer->getMoney() > prop->getCost())
    {
        if (prop->getUpgrades() < 5)
        {
            prop->upgrade();
            state = States::UPDATE_BOARD;
            return true;
        }
    }
    return false;
}

//Handles the output and is used to send the messages out
bool StateMachine::execOutputs(playerMove inMsg, bool flag)
{ // FIX MESSAGES HERE (playerMove)

    if (state == States::UPDATE_BOARD)
    {
        Player *currPlayer = board->getCurrentPlayer();
        if (flag)
        { // if flag is true, valid move.  process based on client or server
            if (isClient)
            { // if client, redraw frames
                glutPostRedisplay();
            } else
            {
                std::cout << "valid move" << std::endl;
                
                this->serv->sendToClient(inMsg);
                
            }
        }
        else
        {
            std::cout << "invalid move" << std::endl;
            inMsg.moveType = 0; // invalid move.
            this->serv->sendToClient(inMsg);
        }

        if (board->checkForEndCond())
        { // need to write check for end conditions function
            state = States::GAME_EXIT;
        }
        else
        {
            state = States::USER_INPUT;
        }
    }
    else if (state == States::GAME_SETUP)
    {
        if (board->checkForStartCond())
        { // need to write check for start conditions function
            // std::cout << "starting game" << std::endl;
            state = States::USER_INPUT;
            board->setCurrPlayer(board->getPlayers().at(0));
        }
        else
        {
            state = States::GAME_SETUP;
        }
        if (!isClient)
        {
            // std::cout << "sending same message" << std::endl;
            if (inMsg.moveType == 'J' || inMsg.moveType =='j') {
                serv->retroJoin();
            } else {
                this->serv->sendToClient(inMsg);
            }
        }
    }
    if (isClient) {
        glutPostRedisplay();
    }
    return true;
}

//Returns the server pointer
server *StateMachine::getServer() { return serv; }

//Sets the server with the server pointer passed
void StateMachine::setServer(server *serv) { this->serv = serv; }

//Sets the board with the board argument passed
void StateMachine::setBoard(Board *board) { this->board = board; }

//Default destructor
StateMachine::~StateMachine(){};