#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
class BoardSpace;
class Property;
class Board;

class Player {
    private:
    Board* board;
    std::string name;
    std::string addr;
    long money;
    BoardSpace* boardSpace; // this is actually a pointer to a boardSpace Object.
    public:
    Player(std::string, Board*);
    Player(std::string);
    Player();
    void buy(Property*);
    void sell(Property*);
    void addMoney(long);
    void takeMoney(long);
    void movePlayer(int); // moves it a certain number of spaces on the board
    void movePlayer(BoardSpace*); // moves a player directly to a space.
    long getMoney();
    std::string getAddr() const;
    void setAddr(std::string);
    BoardSpace* getSpace() const;
    
};

#endif
