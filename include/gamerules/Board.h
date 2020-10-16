#ifndef BOARD_H
#define BOARD_H

#include <gamerules/BoardSpace.h>
#include <gamerules/Player.h>

#include <vector>
class Board {
    private:
    std::string name;
    BoardSpace* head;
    BoardSpace* tail;
    std::vector<Player*> players;
    long length;

    public:
    Board(std::string);
    void addSpace(BoardSpace*);
    // void removeSpace(BoardSpace*); I don't see a need for this method
    // but if we end up using it we can implement it.
    Board& operator<<(BoardSpace*);
    void addPlayer(Player*);
    ~Board();

};

#endif