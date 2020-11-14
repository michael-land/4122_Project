#ifndef BOARDSPACE_H
#define BOARDSPACE_H

#include <string>
#include <gamerules/Property.h>
#include <render/Colors.h>
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
    std::string name;
    Property* property;
    BoardSpace* nextSpace;
    BoardSpace* prevSpace;
    Colors color;


    public:
    BoardSpace(std::string, Property*, Colors);
    std::string getName() const;
    void setName(const std::string&);
    const Property* getProperty() const;
    void setProperty(Property*);
    BoardSpace* getNextSpace() const;
    BoardSpace* getPrevSpace() const;
    void setNextSpace(BoardSpace*);
    void setPrevSpace(BoardSpace*);
    void setColor(Colors color);
    Colors getColor();
    ~BoardSpace();   

};

#endif