#include <statemachine/States.h>

#ifndef SSM_H
#define SSM_H

class ServerStateMachine {
    private:
    States state;

    public:
    States getCurrentState();
    void input(int);
    void execOutputs();
};

#endif