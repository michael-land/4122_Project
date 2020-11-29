cmake_minimum_required(VERSION 3.0.0)
project(techopoly VERSION 0.1.0)

include(CTest)
enable_testing()

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
    src/builder/BoardBuilder.cpp
    src/multiplayer/MultiplayerObjects.cpp
    src/statemachine/StateMachine.cpp)

add_executable(Technopoly Technopoly.cpp)
target_link_libraries(Technopoly gamelib)
target_link_libraries(Technopoly GL GLU glut)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
