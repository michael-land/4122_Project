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

void StateMachine::setIsClient(bool isClient) {
    this->isClient = isClient;
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
    
    // if able to set current player to next player
    // return true;
    return false;
}

bool StateMachine::processJoin(playerMove inMsg) { // a join is represented by the "J" character, although that isn't necessarily a keyboard option.    
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

bool StateMachine::execOutputs(playerMove inMsg, bool flag) {
    boardInfo outMsg;
    if (state == States::UPDATE_BOARD) {
        Player *currPlayer = board->getCurrentPlayer();        
        if (flag) // if flag is true, valid move.  process based on client or server
        {
            if (isClient) { // if client, redraw frames
                // redisplay frames (openGL)
            }
            else { // if server, send message back to clients		    
                outMsg.moveStatus = true;
                outMsg.movePosition = currPlayer->getSpace()->getSpaceID();  // currPlayer->getSpace should return a boardspace object, then call getSpaceID() for that boardspace object to get int ID
                outMsg.moveType = inMsg.moveType;
                outMsg.playerID = currPlayer->getName();
                this->serv->sendToClient(outMsg);
            }
        }
        else
        { // if flag is false, invalid move; send invalid move update to client
            outMsg.moveStatus = false;
            outMsg.movePosition = NULL;
            outMsg.moveType = NULL;
            outMsg.playerID = currPlayer->getName();
            this->serv->sendToClient(outMsg);
        }
           
        if (board->checkForEndCond()) { // need to write check for end conditions function
            state = States::GAME_EXIT;
        } else {
            state = States::USER_INPUT;
        }

        } else if (state == States::GAME_SETUP) {
        if (board->checkForStartCond()) {  // need to write check for start conditions function
            state = States::USER_INPUT;
        } else {
            state = States::GAME_SETUP;
        }
        outMsg.moveStatus = true;
        outMsg.movePosition = NULL;  // currPlayer->getSpace should return a boardspace object, then call getSpaceID() for that boardspace object to get int ID
        outMsg.moveType = inMsg.moveType;
        outMsg.playerID = inMsg.playerID;
        this->serv->sendToClient(outMsg);
    }
    return true;
}