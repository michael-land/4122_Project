#include <statemachine/States.h>
#include <statemachine/Decision.h>
#include <gamerules/Player.h>

class Board;
class server;
struct playerMove;
struct playerMove;
#ifndef SSM_H
#define SSM_H

class StateMachine {
    private:
    server *serv;
    States state;
    Board* board;
    bool isClient;
    public:
    StateMachine();
    States getCurrentState() const;
    bool input(playerMove inMsg);
    bool processBuy();
    bool processSell();
    bool processUpgrade();
    bool processRollDice(int numSpaces);
    bool processEndTurn();
    bool execOutputs(playerMove);
	bool processJoin(playerMove);

};

#endif