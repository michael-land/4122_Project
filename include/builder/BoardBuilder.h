#include <gamerules/Board.h>
#include <gamerules/Property.h>

class BoardBuilder {
    private:
    int numSpaces;
    Board* board;
    void construct();
    std::vector<Property*> props;
    std::vector<std::string> spaceNames;
    int foo;

    public:
    BoardBuilder();
    
    Board* getBoard();
};