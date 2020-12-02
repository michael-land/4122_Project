/*
Authors: Christopher Kennedy, Jackson Stanhope, Jim O'Donnell, Michael Zhou Lu, Ruben Quiros, and Shelby Crisp 
Class: ECE 4122
Last Date Modified: 12/1/20

Description:
This is the file that defines the functionality for the client main program.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <multiplayer/MultiplayerObjects.h>
#include <statemachine/States.h>
#include <gamerules/Player.h>
#include <statemachine/StateMachine.h>
#include <render/BoardRenderer.h>

#define PORT 6500

// Driver code
int main(int argc, char** argv) {

    std::string serverIP;
    std::string un;
    std::cout << "IP address of server: ";
    std::cin >> serverIP;

    std::cout << "Please pick a 4 digit username: ";
    std::cin >> un;

    while (un.length() > 4) {
		cout << "Incorrect length.  Please pick a 4 digit username.";
		cin >> un;
	}

    // playerMove initMsg;
    // strcpy(initMsg.playerID, username.c_str());
    // initMsg.moveType = 'J';
    // initMsg.playerRoll = 0;

	// cout << "before client init" << endl;
    GLRenderShared::username = un;
	client *GameClient = new client(PORT, serverIP.c_str() );
    // GLRenderShared::username = username;
    // cout << "after client initialized" << endl;
    GLRenderShared::cli = GameClient;
    // setup(argc, argv); // openGL setup
    std::thread openGLThread(setup, argc, argv);
    bool gameStarted = false;
    while (GameClient->getSSM()->getCurrentState() != States::GAME_EXIT) {
        // std::cout << "in whileloop" << std::endl;
        // std::cout << GameClient->getSSM()->getCurrentState() << std::endl;
        if ((GameClient->getSSM()->getCurrentState() != States::GAME_SETUP) & !gameStarted) {
            // std::cout << "client game started" << std::endl;
            GLRenderShared::board = GameClient->getPlayingBoard();
            glutPostRedisplay();
            gameStarted = true;
        }
    }
    std::cout << "Client exited" << std::endl;
}