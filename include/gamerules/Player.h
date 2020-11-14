#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
class BoardSpace;

class Player {
    private:
    std::string name;
    long money;
    BoardSpace* boardSpace; // this is actually a pointer to a boardSpace Object.
    public:
    
};

#endif