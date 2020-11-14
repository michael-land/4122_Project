# Buzzopoly

# Game Engine Information
## Overview
## API
- Board
- BoardSpace
- Property
- Player

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
