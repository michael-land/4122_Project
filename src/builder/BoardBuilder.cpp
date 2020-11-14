#include <builder/BoardBuilder.h>

BoardBuilder::BoardBuilder() {
    this->numSpaces = 40;

    construct();
}

void BoardBuilder::construct() {
    Board* board = new Board("Technopoly");
    Property* prop;
    BoardSpace* boardSpace;

    // created from Ruben's board layout doc
    prop = new Property("Scheller College of Business", 100, 100);
    boardSpace = new BoardSpace("SCoB", prop, Colors::BROWN);
    board->addSpace(boardSpace);

    prop = new Property("GTRI", 100, 100);
    boardSpace = new BoardSpace("GTRI", prop, Colors::BROWN);
    board->addSpace(boardSpace);

    prop = new Property("North Avenue Apartments", 100, 100);
    boardSpace = new BoardSpace("Nave", prop, Colors::LIGHT_BLUE);
    board->addSpace(boardSpace);

    prop = new Property("The Varsity", 100, 100);
    boardSpace = new BoardSpace("The Varsity", prop, Colors::LIGHT_BLUE);
    board->addSpace(boardSpace);

    prop = new Property("MARTA", 100, 100);
    boardSpace = new BoardSpace("MARTA", prop, Colors::LIGHT_BLUE);
    board->addSpace(boardSpace);

    prop = new Property("Student Center", 100, 100);
    boardSpace = new BoardSpace("Student Center", prop, Colors::PINK);
    board->addSpace(boardSpace);

    prop = new Property("Ferst Center for the Arts", 100, 100);
    boardSpace = new BoardSpace("Ferst Center for the Arts", prop, Colors::PINK);
    board->addSpace(boardSpace);

    prop = new Property("Tech Green", 100, 100);
    boardSpace = new BoardSpace("Tech Green", prop, Colors::PINK);
    board->addSpace(boardSpace);

    prop = new Property("East Village", 100, 100);
    boardSpace = new BoardSpace("East Village", prop, Colors::ORANGE);
    board->addSpace(boardSpace);

    prop = new Property("West Village", 100, 100);
    boardSpace = new BoardSpace("West Village", prop, Colors::ORANGE);
    board->addSpace(boardSpace);

    prop = new Property("Woodruff", 100, 100);
    boardSpace = new BoardSpace("Woodruff", prop, Colors::ORANGE);
    board->addSpace(boardSpace);

    prop = new Property("Clough Undergraduate Learning Commons", 100, 100);
    boardSpace = new BoardSpace("Clough Undergraduate Learning Commons", prop, Colors::RED);
    board->addSpace(boardSpace);

    prop = new Property("Klaus Advanced Computing", 100, 100);
    boardSpace = new BoardSpace("Klaus Advanced Computing", prop, Colors::RED);
    board->addSpace(boardSpace);

    prop = new Property("Library", 100, 100);
    boardSpace = new BoardSpace("Library", prop, Colors::RED);
    board->addSpace(boardSpace);

    prop = new Property("Kendeda", 100, 100);
    boardSpace = new BoardSpace("Kendeda", prop, Colors::YELLOW);
    board->addSpace(boardSpace);

    prop = new Property("College of Computing", 100, 100);
    boardSpace = new BoardSpace("College of Computing", prop, Colors::YELLOW);
    board->addSpace(boardSpace);

    prop = new Property("McCamish Pavilion", 100, 100);
    boardSpace = new BoardSpace("McCamish Pavilion", prop, Colors::YELLOW);
    board->addSpace(boardSpace);

    prop = new Property("Van Leer", 100, 100);
    boardSpace = new BoardSpace("Van Leer", prop, Colors::GREEN);
    board->addSpace(boardSpace);

    prop = new Property("The Hive", 100, 100);
    boardSpace = new BoardSpace("The Hive", prop, Colors::GREEN);
    board->addSpace(boardSpace);

    prop = new Property("Russ Chandler Stadium", 100, 100);
    boardSpace = new BoardSpace("Russ Chandler Stadium", prop, Colors::GREEN);
    board->addSpace(boardSpace);

    prop = new Property("The Hive", 100, 100);
    boardSpace = new BoardSpace("The Hive", prop, Colors::BLUE);
    board->addSpace(boardSpace);

    prop = new Property("Russ Chandler Stadium", 100, 100);
    boardSpace = new BoardSpace("Russ Chandler Stadium", prop, Colors::BLUE);
    board->addSpace(boardSpace);

    boardSpace = new BoardSpace("Chance", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    boardSpace = new BoardSpace("Chance", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    boardSpace = new BoardSpace("Chance", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    boardSpace = new BoardSpace("Jacket Chest", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    boardSpace = new BoardSpace("Jacket Chest", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    boardSpace = new BoardSpace("Jacket Chest", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    boardSpace = new BoardSpace("Tuition", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    boardSpace = new BoardSpace("Mandatory Fees", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    boardSpace = new BoardSpace("Laundry", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    boardSpace = new BoardSpace("Dining Halls", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    boardSpace = new BoardSpace("Blue Route", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    boardSpace = new BoardSpace("Red Route", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    boardSpace = new BoardSpace("Tech Trolley", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    boardSpace = new BoardSpace("Tech Express", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    boardSpace = new BoardSpace("Go Jackets", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    boardSpace = new BoardSpace("Academic Probation", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    boardSpace = new BoardSpace("Go to Academic Probation", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    boardSpace = new BoardSpace("Free Space", nullptr, Colors::WHITE);
    board->addSpace(boardSpace);
    
}