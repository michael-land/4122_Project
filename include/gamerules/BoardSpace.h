/*
Authors: Christopher Kennedy, Jackson Stanhope, Jim O'Donnell, Michael Zhou Lu, Ruben Quiros, and Shelby Crisp 
Class: ECE 4122
Last Date Modified: 12/1/20
Description:
 * This class is essentially a linked list node for
 * the 'Board' class, which contains implementation
 * for the game board as a linked list.
 * This class also contains a property, which is the 
 * property that players can own/have to pay rent to on the
 * board tile, and a vector containing pointers
 * to player objects that are currently at that tile.
*/

#ifndef BOARDSPACE_H
#define BOARDSPACE_H

#include <string>
#include <vector>
class Player;

class BoardSpace {
    private:
    int spaceID;    //ID for that given boardspace
    std::string name;   //Name of that space
    BoardSpace* nextSpace;  //Pointer to the next space
    BoardSpace* prevSpace;  //Pointer to the previous space
    std::vector<Player*> playersOnSpace;    //Vector of players on that given space
    int improvements; // this is for houses, hotels, etc.  

    public:
    BoardSpace(std::string);    //Constructor being passed a string name
    std::string getName() const;    //Returns the name of the boardspace
    void setName(const std::string&);   //Sets the name for the boardspace
    BoardSpace* getNextSpace() const;   //Returns a pointer to the next board space
    BoardSpace* getPrevSpace() const;   //Returns a pointer to the previous boardspace
    void setNextSpace(BoardSpace*);     //Sets the next board space to the pointer passed
    void setPrevSpace(BoardSpace*);     //Sets the previous board space to the pointer passed
    void setSpaceID(const int&);    //Sets the space id with the int passed
    int getSpaceID() const;     //Returns the space id 
    ~BoardSpace();  //Destructor
    virtual void placeholder(); 

};

#endif
