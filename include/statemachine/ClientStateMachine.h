#include <statemachine/States.h>

#ifndef CSM_H
#define CSM_H

class ClientStateMachine {
    private:
    States state;

    public:
    States getCurrentState();
    void input(int);
    void execOutputs();
};

#endif