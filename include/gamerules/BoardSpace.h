#ifndef BOARDSPACE_H
#define BOARDSPACE_H

#include <string>
#include <vector>
#include <render/Colors.h>
class Player;
/*
 * This class is essentially a linked list node for
 * the 'Board' class, which contains implementation
 * for the game board as a linked list.
 * This class also contains a property, which is the 
 * property that players can own/have to pay rent to on the
 * board tile, and a vector containing pointers
 * to player objects that are currently at that tile.
 */
class BoardSpace {
    private:
    std::string spaceID;
    std::string name;
    BoardSpace* nextSpace;
    BoardSpace* prevSpace;
    Colors color;
    int improvements; // this is for houses, hotels, etc.

    public:
    BoardSpace(std::string, Colors);
    std::string getName() const;
    void setName(const std::string&);
    std::string getSpaceID() const;
    void setSpaceID(const std::string&);
    BoardSpace* getNextSpace() const;
    BoardSpace* getPrevSpace() const;
    void setNextSpace(BoardSpace*);
    void setPrevSpace(BoardSpace*);
    void setColor(Colors color);
    Colors getColor();

    ~BoardSpace();   

};

#endif