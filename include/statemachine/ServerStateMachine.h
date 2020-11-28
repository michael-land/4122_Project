#include <statemachine/States.h>
#include <statemachine/Decision.h>
#ifndef SSM_H
#define SSM_H

class ServerStateMachine {
    private:
    States state;

    public:
    ServerStateMachine();
    States getCurrentState() const;
    Decision input(unsigned char);
    void processDecision(Decision);
    void execOutputs();
};

#endif