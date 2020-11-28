#ifndef BOARD_H
#define BOARD_H

#include <gamerules/BoardSpace.h>
#include <gamerules/Player.h>
#include <vector>

class ServerStateMachine;

class Board {
    private:
    std::string name;
    BoardSpace* head;
    BoardSpace* tail;
    std::vector<Player*> players;
    Player* currPlayer;
    long length;
    ServerStateMachine* ssm;

    public:
    Board(std::string);
    void addSpace(BoardSpace*);
    Board& operator<<(BoardSpace*);
    void addPlayer(Player*);
    int rollDice() const;
    Player* getCurrentPlayer();
    std::vector<Player*> getPlayers();
    BoardSpace* getHead() const;
    ServerStateMachine* getSSM();
    ~Board();

};

#endif