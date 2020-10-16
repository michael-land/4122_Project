cmake_minimum_required(VERSION 3.0.0)
project(techopoly VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(include/
                    include/gamerules)

add_library(gamelib
    src/gamerules/BoardSpace.cpp
    src/gamerules/Property.cpp
    src/gamerules/Board.cpp
    src/gamerules/Player.cpp)

add_executable(Technopoly Technopoly.cpp)
target_link_libraries(Technopoly gamelib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
