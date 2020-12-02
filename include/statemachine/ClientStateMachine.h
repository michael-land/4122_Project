/*
Authors: Christopher Kennedy, Jackson Stanhope, Jim O'Donnell, Michael Zhou Lu, Ruben Quiros, and Shelby Crisp 
Class: ECE 4122
Last Date Modified: 12/1/20
Description:
This is the header file the client state machine. 
*/
#include <statemachine/States.h>

#ifndef CSM_H
#define CSM_H

//Clients state machine 
class ClientStateMachine {
    private:
    States state;   //Holds a state for the client state machine

    public:
    States getCurrentState();   //Returns the current state for that client
    void input(int);    //Adds an int input to the state
    void execOutputs(); //Executes the outputs for that state
};

#endif
