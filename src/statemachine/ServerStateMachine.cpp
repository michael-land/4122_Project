#include <statemachine/ServerStateMachine.h>

ServerStateMachine::ServerStateMachine() {
    this->state = States::GAME_SETUP;
}

States ServerStateMachine::getCurrentState() const {
    return this->state;
}

Decision ServerStateMachine::input(unsigned char in) {
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

void ServerStateMachine::processDecision(Decision dec) {
    
}