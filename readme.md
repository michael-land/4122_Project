# Buzzopoly

## Authors/Collaborators
1. Jackson Stanhope
2. Shelby Crisp
3. Zhou (Michael) Lu
4. James O'Donnell
5. Ruben Quiros
6. Chris Kennedy

## Credits

Credit goes to Dr. Hurley ffrom Georgia Tech or the following functions: init(), reshape(), keyboard(), and main() in "BoardRenderer.h", and for "Bitmap.h". These were inspired by his in-class examples for OpenGL. There are other snippets of code for coloring, lighting, buffering, and depth perception that were also taken from his examples from lectures. MultiplayerObjects.cpp was inspired by the code given from Dr. Hurley's Assignment 4 (OpenGL) shell code as well as his Assignment 5 UDP Socket code.

All References to "Buzz" and names of school buildings/locations are trademarks of the Georgia Institute of Technology (Gatech/Georgia Tech).

The game itself is inspired by Monopoly, which is Property of Hasbro.

## How to Build on Pace-ICE
- Environment: Ubuntu Linux / Red Had Enterprise Linux
- Packages Required: OpenGL/freeglut and Core/mesa
  - At this point, we can only run our project locally, but with more time we would have liked to make it run across a network
- Run the Following Commands for Pace-ICE

```
module purge
module load gcc/9.2.0
module use /storage/home/hcocice1/shared-classes/modules/ lmod/linux-rhel7-x86_64/
module load Core/mesa Core/mesa-glu
```

- In order to view the Graphics of the game, please either run PACE with a VNC session or setup X forwarding.
    - This process should be the same as in Assignment 4 (OpenGL) 


1. Build the Software: Open a Terminal and Run 
```
./build.sh
```
2. Run the server
```
./server
```
    
- The server will output it's own IP address, which is necessary for the client to use

3. Open a new Terminal, Run the client for the first player
```
./client
```
4. The client will need to input the server's IP address in the format it was given by the server at this stage

5. Input the name of the first player as prompted

6. Open a new Terminal, Run the client of the second player
```
./client
```
7. Input the server's IP as done in step 4
8. Input the name of the second player as prompted

9. Play the game by pressing the keys described by the menu on the screen

    - The Menus are as below:
```
    B: Buy a property
    S: Sell a property
    H: Build a house/hotel
    J: Join a game
    R: Roll the dice
    N: End your turn
    T: Rotate the board
```
## Rubric Attainment Report (for the benefit of the Grader)
- Functions work as expected
    - With the complexity of our project, some functionality has been simplified, but basic multiplayer functionality is available. 
      - Two clients are able to connect to a server and perform rudimentary operations    
- Custom classes are used
    - Over 10 custom classes are used!
- The following special topics are used:
    - Multithreading (std::thread)
    - Sockets
    - OpenGL
- Clear documenting coding styles are used
    - All functions are commented with what the function does
    - Comment header are located at the top of files to explain the overall functionality


## Game Engine Information
### Overview
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
### API
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

### A note on circular dependencies
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


