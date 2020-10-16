#ifndef PLAYER_H
#define PLAYER_H

#include <gamerules/BoardSpace.h>

class Player {
    private:
    std::string name;
    long money;
    BoardSpace* currentSpace;
};

#endif