#include <statemachine/StateMachine.h>
#include <gamerules/Board.h>
#include <gamerules/Property.h>
#include <multiplayer/MultiplayerObjects.h>

StateMachine::StateMachine() {
    this->state = States::GAME_SETUP;
}

States StateMachine::getCurrentState() const {
    return this->state;
}

bool StateMachine::input(playerMove inMsg) { // pass message in here
    bool flag;
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
        default:
        break;
    }
    if (flag) {
        execOutputs(inMsg);
    }
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
            return true;
        }
    }
    return false;
}

bool StateMachine::processRollDice(int numSpaces) {
    if (numSpaces > 12) {
        return false;
    }
	Player* currPlayer = board->getCurrentPlayer();
	currPlayer->movePlayer(numSpaces);
	return true;
}

bool StateMachine::processEndTurn() {
    
    // if able to set current player to next player
    // return true;
    return false;
}

bool StateMachine::processJoin(playerMove inMsg) { // a join is represented by the "J" character, although that isn't necessarily a keyboard option.
    
    if (state != States::GAME_SETUP) {
        return false;
    }
    auto playerVec = board->getPlayers();
    std::string str(inMsg.playerID);;
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
    return false;
}

bool StateMachine::execOutputs(playerMove inMsg) {
    if (state == States::USER_INPUT) {
        state = States::UPDATE_BOARD;
    } else {
        return false;
    }
    boardInfo outMsg;
    // build the outMsg

    // call some function like
    // server.sendMessageToClients(outMsg);

    // server.updateBoard()

}