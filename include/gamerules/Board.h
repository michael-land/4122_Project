#ifndef BOARD_H
#define BOARD_H

#include <gamerules/BoardSpace.h>
#include <gamerules/Player.h>
#include <vector>

class StateMachine;

class Board {
    private:
    std::string name;
    BoardSpace* head;
    BoardSpace* tail;
    std::vector<Player*> players;
    Player* currPlayer;
    long length;
    StateMachine* ssm;

    public:
    Board(std::string);
    void addSpace(BoardSpace*);
    Board& operator<<(BoardSpace*);
    void addPlayer(Player*);
    int rollDice() const;
    Player* getCurrentPlayer();
    std::vector<Player*> getPlayers();
    BoardSpace* getHead() const;
    StateMachine* getSSM();
    BoardSpace* getTail() const;
    ~Board();
    BoardSpace* findSpace(int);
    BoardSpace* findSpace(std::string);
};

#endif