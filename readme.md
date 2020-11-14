# Buzzopoly

# Game Engine Information
## Overview
- Board
    - contains most information about the game
    - includes handles to board spaces, players, etc.
    - comes with dice!
- BoardSpace
    - includes a pointer to players on that space
    - has a name
    - has a spaceID (for locating the space on the board)
- Property
    - inherits from BoardSpace
    - includes information about rent/prices/etc.
    - has a pointer to the owner of *this property.
- Player
    - represents "server side" knowledge of a player
    - has a pointer to all BoardSpaces owned by *this player.
    - has a pointer to current BoardSpace (see section on circular dependencies)
    - keeps track of money
    - has a handle on PlayerClient
- PlayerClient
    - network logic
    - has a handle on a Player class
## API
- Board
    - Board(std::string);
    - void addSpace(BoardSpace*);
    - Board& operator<<(BoardSpace*);
    - void addPlayer(Player*);
    - int rollDice() const;
    - Player* getCurrentPlayer();
    - std::vector<Player*> getPlayers();
- BoardSpace
    - BoardSpace(std::string, Colors);
    - std::string getName() const;
    - void setName(const std::string&);
    - std::string getSpaceID() const;
    - void setSpaceID(const std::string&);
    - BoardSpace* getNextSpace() const;
    - BoardSpace* getPrevSpace() const;
    - void setNextSpace(BoardSpace*);
    - void setPrevSpace(BoardSpace*);
    - void setColor(Colors color);
    - Colors getColor();
- Property
    - Property(std::string, long, long, Colors);
    - long getRent() const;
    - long getCost() const;
    - void setRent(const long&);
    - void setCost(const long&);
    - std::string getName() const;
    - void setName(const std::string&);
- Player
    - void buy(Property*);
    - void sell(Property*);
    - void addMoney(long);
    - void takeMoney(long);
    - void movePlayer(int); // moves it a certain number of spaces on the board
    - void movePlayer(BoardSpace*); // moves a player directly to a space.

## A note on circular dependencies
Because there are many objects that point to each other (ex: BoardSpace points to Player, and Player points to BoardSpace) special considerations have been made to avoid build issues. Here is the solution:


```cpp
//foo.h
class bar; // notice that foo.h does not include bar.h
class foo {
    private:
    bar* b;
    public:
    void doSomething(bar*);
};
```

```cpp
//foo.cpp
#include "foo.h"
#include "bar.h" // the include for bar.h belongs in foo's implementation file.
void foo::doSomething(bar* b) {
    // logic
}
```

A similar method is used in bar.h and bar.cpp, not shown.
