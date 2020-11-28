#include <statemachine/ServerStateMachine.h>
#include <gamerules/Board.h>
#include <gamerules/Property.h>
#include <multiplayer/MultiplayerObjects.h>

ServerStateMachine::ServerStateMachine() {
    this->state = States::GAME_SETUP;
}

States ServerStateMachine::getCurrentState() const {
    return this->state;
}

bool ServerStateMachine::input(playerMove inMsg) { // pass message in here
    switch(inMsg.moveType) {
        case 'b':
        case 'B':
        return processBuy();
        break;

        case 's':
        case 'S':
        return processSell();
        break;

        case 'r':
        case 'R':
        return processRollDice(inMsg.playerRoll);
        break;

        case 'h':
        case 'H':
        return processUpgrade();
        break;

        case 'n':
        case 'N':
        return processEndTurn();
        break;
        default:
        break;
    }
}

bool ServerStateMachine::processBuy() {
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
            return true;
        }
    }
    return false;
}

bool ServerStateMachine::processSell() {
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
            return true;
        }
    }
    return false;
}

bool ServerStateMachine::processRollDice(int numSpaces) {
    if (numSpaces > 12) {
        return false;
    }
	Player* currPlayer = board->getCurrentPlayer();
	currPlayer->movePlayer(numSpaces);
	return true;
}

bool ServerStateMachine::processEndTurn() {
    
    // send update message to all clients w/ state of the game
}

void ServerStateMachine::processJoin() {
    
    // receive message from client, add player to game if player does not exist
}

bool ServerStateMachine::processUpgrade() {
    Player* currPlayer = board->getCurrentPlayer();
    BoardSpace* space = currPlayer->getSpace();
    Property* prop = dynamic_cast<Property*>(space);
    if (!prop) {
        return false;
    }
    if (prop->getOwner() == currPlayer && currPlayer->getMoney() > prop->getCost()) {
        if (prop->getUpgrades() < 5 ) {
            prop->upgrade();
            return true;
        }
    }
}