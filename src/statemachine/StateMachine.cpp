#include <statemachine/StateMachine.h>
#include <gamerules/Board.h>
#include <gamerules/Property.h>
#include <multiplayer/MultiplayerObjects.h>
#include <GL/glut.h>
#include <iostream>

StateMachine::StateMachine() {
    this->state = States::GAME_SETUP;
}

States StateMachine::getCurrentState() const {
    return this->state;
}

void StateMachine::setIsClient(bool isClient) {
    this->isClient = isClient;
}

bool StateMachine::input(playerMove inMsg) { // pass message in here
    bool flag;
    std::cout << "inputs" << std::endl;
    switch(inMsg.moveType) {
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

bool StateMachine::processBuy() {
    Player* currPlayer = board->getCurrentPlayer();
    BoardSpace* space = currPlayer->getSpace();
    Property* prop;
    if (state == States::USER_INPUT) {
        prop = dynamic_cast<Property*>(space);
        if(!prop) {
            return false;
        }        
        if (currPlayer->getMoney() > prop->getCost()) {
            currPlayer->buy(prop);
            state = States::UPDATE_BOARD;
            return true;
        }
    }
    return false;
}

bool StateMachine::processSell() {
    Player* currPlayer = board->getCurrentPlayer();
    BoardSpace* space = currPlayer->getSpace();
    Property* prop;
    if (state == States::USER_INPUT) {
        prop = dynamic_cast<Property*>(space);
        if(!prop) {
            return false;
        }        
        if (prop->getOwner() == currPlayer) {
            currPlayer->sell(prop);
            state = States::UPDATE_BOARD;
            return true;
        }
    }
    return false;
}

bool StateMachine::processRollDice(int numSpaces) {
    if (state != States::USER_INPUT) {
        return false;
    }
    if (numSpaces > 12) {
        return false;
    }
	Player* currPlayer = board->getCurrentPlayer();
	currPlayer->movePlayer(numSpaces);
    state = States::UPDATE_BOARD;
	return true;
}

bool StateMachine::processEndTurn() {
	this->board->swapCurrPlayer(); // swap current player to other player in vector
	// if able to set current player to next player
	// return true;
	return false;
}

bool StateMachine::processJoin(playerMove inMsg) { // a join is represented by the "J" character, although that isn't necessarily a keyboard option.
    std::cout << "Player Joining!" << std::endl;    
    if (state != States::GAME_SETUP) {
        return false;
    }
    auto playerVec = board->getPlayers();
    std::string str(inMsg.playerID);
    bool exists;
    for (std::vector<Player*>::iterator it = playerVec.begin(); it < playerVec.end(); it++) {        
        if ((*it)->getName() == str){
            exists = true;
        }
    }    
    if (!exists) {
        Player* newPlayer = new Player(str, this->board);
        this->board->addPlayer(newPlayer);
        return true;
    }
    return false;
}

bool StateMachine::processUpgrade() {
    if (state != States::USER_INPUT) {
        return false;
    }
    Player* currPlayer = board->getCurrentPlayer();
    BoardSpace* space = currPlayer->getSpace();
    Property* prop = dynamic_cast<Property*>(space);
    if (!prop) {
        return false;
    }
    if (prop->getOwner() == currPlayer && currPlayer->getMoney() > prop->getCost()) {
        if (prop->getUpgrades() < 5 ) {
            prop->upgrade();
            state = States::UPDATE_BOARD;
            return true;
        }
    }
    return false;
}

bool StateMachine::execOutputs(playerMove inMsg, bool flag) {  // FIX MESSAGES HERE (playerMove)
    playerMove outMsg;
    if (state == States::UPDATE_BOARD) {
        Player *currPlayer = board->getCurrentPlayer();        
        if (flag) { // if flag is true, valid move.  process based on client or server
            if (isClient) { // if client, redraw frames
                glutPostRedisplay();
            }
            else { 
                this->serv->sendToClient(inMsg);
            }
        }
        else { 
            inMsg.moveType = 0; // invalid move.
            this->serv->sendToClient(inMsg);
        }
           
        if (board->checkForEndCond()) { // need to write check for end conditions function
            state = States::GAME_EXIT;
        } else {
            state = States::USER_INPUT;
        }

        } else if (state == States::GAME_SETUP) {
        if (board->checkForStartCond()) {  // need to write check for start conditions function
            state = States::USER_INPUT;
            board->setCurrPlayer(board->getPlayers().at(0));
        } else {
            state = States::GAME_SETUP;
        }
        this->serv->sendToClient(outMsg);
    }
    return true;
}

server *StateMachine::getServer() { return serv; }

void StateMachine::setServer(server* serv) { this->serv = serv; }

StateMachine::~StateMachine() { };