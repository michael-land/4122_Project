cmake_minimum_required(VERSION 2.8.12)
project(buzzopoly)

include_directories(include/
                    include/gamerules
                    include/builder
                    include/render
                    include/multiplayer
                    include/statemachine)

add_library(gamelib
    src/gamerules/BoardSpace.cpp
    src/gamerules/Property.cpp
    src/gamerules/Board.cpp
    src/gamerules/Player.cpp
    src/builder/BoardFactory.cpp
    src/multiplayer/MultiplayerObjects.cpp
    src/statemachine/StateMachine.cpp)

add_executable(server Server.cpp)
target_link_libraries(server gamelib pthread GLU GL glut)

add_executable(client Client.cpp)
target_link_libraries(client gamelib pthread GLU GL glut)
