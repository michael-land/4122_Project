#include <statemachine/States.h>
#include <statemachine/Decision.h>
class Board;
#ifndef SSM_H
#define SSM_H

class ServerStateMachine {
    private:
    States state;
    Board* board;
    public:
    ServerStateMachine();
    States getCurrentState() const;
    bool input(unsigned char);
    bool processBuy();
    bool processSell();
    bool processUpgrade();
    bool processRollDice();
    bool processEndTurn();
    void execOutputs();
};

#endif