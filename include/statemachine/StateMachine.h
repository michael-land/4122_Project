#include <statemachine/States.h>
#include <statemachine/Decision.h>
#include <gamerules/Player.h>
class Board;
#ifndef SSM_H
#define SSM_H

class ServerStateMachine {
    private:
    States state;
    Board* board;
    bool isClient;
    public:
    ServerStateMachine();
    States getCurrentState() const;
    bool input(playerMove inMsg);
    bool processBuy();
    bool processSell();
    bool processUpgrade();
    bool processRollDice(int numSpaces);
    bool processEndTurn();
    void execOutputs(playerMove inMsg);
	void processJoin();

};

#endif