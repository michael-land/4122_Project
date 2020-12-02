#!/bin/bash
# mkdir build
# g++ -c -Iinclude/ src/gamerules/Player.cpp -o build/Player.o
# g++ -c -Iinclude/ src/gamerules/Board.cpp -o build/Board.o
# g++ -c -Iinclude/ src/gamerules/BoardSpace.cpp -o build/BoardSpace.o
# g++ -c -Iinclude/ src/gamerules/Property.cpp -o build/Property.o
# g++ -c -Iinclude/ src/statemachine/StateMachine.cpp -o build/StateMachine.o
# g++ -c -Iinclude/ src/multiplayer/MultiplayerObjects.cpp -o build/MultiplayerObjects.o
# g++ -c -Iinclude/ src/builder/BoardFactory.cpp -o build/BoardFactory.o
# g++ -c -Iinclude/ Server.cpp -o build/Server.o
# g++ -c -Iinclude/ Client.cpp -o build/Client.o

# g++  -Iinclude/ -lpthread -lGL -lGLU -lglut build/Client.o build/Player.o build/Board.o build/BoardSpace.o build/Property.o build/StateMachine.o build/MultiplayerObjects.o build/BoardFactory.o -o client

g++ -c -g -Iinclude -lpthread -lGL -lGLU -lglut src/gamerules/Player.cpp src/gamerules/Board.cpp src/gamerules/BoardSpace.cpp src/gamerules/Property.cpp src/builder/BoardFactory.cpp src/multiplayer/MultiplayerObjects.cpp src/statemachine/StateMachine.cpp Server.cpp 
g++ -o server Board.o BoardFactory.o BoardSpace.o MultiplayerObjects.o Player.o Property.o StateMachine.o Server.o -lGL -lGLU -lglut -lpthread
rm *.o

g++ -c -g -Iinclude -lpthread -lGL -lGLU -lglut src/gamerules/Player.cpp src/gamerules/Board.cpp src/gamerules/BoardSpace.cpp src/gamerules/Property.cpp src/builder/BoardFactory.cpp src/multiplayer/MultiplayerObjects.cpp src/statemachine/StateMachine.cpp Client.cpp 
g++ -o client Board.o BoardFactory.o BoardSpace.o MultiplayerObjects.o Player.o Property.o StateMachine.o Client.o -lGL -lGLU -lglut -lpthread
rm *.o