#include <statemachine/ServerStateMachine.h>
#include <gamerules/Board.h>
#include <gamerules/Property.h>
ServerStateMachine::ServerStateMachine() {
    this->state = States::GAME_SETUP;
}

States ServerStateMachine::getCurrentState() const {
    return this->state;
}

bool ServerStateMachine::input(unsigned char in) {
    switch(in) {
        case 'b':
        case 'B':
        return Decision::BUY;
        break;

        case 's':
        case 'S':
        return Decision::SELL;
        break;

        case 'r':
        case 'R':
        return Decision::ROLL_DICE;
        break;

        case 'h':
        case 'H':
        return Decision::UPGRADE;
        break;

        case 'n':
        case 'N':
        return Decision::END_TURN;
        return;
        default:
        break;
    }
}

bool ServerStateMachine::processBuy() {
    Player* currPlayer = board->getCurrentPlayer();
    BoardSpace* space = currPlayer->getSpace();
    Property* prop;
    if (state == States::USER_INPUT) {
        if (dynamic_cast<Property*>(space) != nullptr) {
            prop = space;
        }
        
        if (currPlayer->getMoney() > 
    }
}
