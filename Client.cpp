#include <stdio.h>
#include <stdlib.h>
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
#include <Player.h>
#include <statemachine/StateMachine.h>
#include <render/BoardRenderer.h>

#define PORT 20123

// Driver code
int main(int argc, char** argv) {
    /*  --> IS ANY OF THIS NECESSARY FOR THE CLIENT?
    char hostbuffer[256];
    char* IPbuffer;
    struct hostent* host_entry;
    int hostname;
    int turnCounter;

    // To retrieve hostname
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    checkHostName(hostname);

    // To retrieve host information
    host_entry = gethostbyname(hostbuffer);
    checkHostEntry(host_entry);

    // To convert an Internet network
    // address into ASCII string
    IPbuffer = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0]));
    std::cout << IPbuffer << std::endl;
    */    

    // user inputs the IP address of the server?
    // include port number AND ip address for new player comparison

    std::string serverIP;

    std::cout << "IP address of server: ";
    std::cin >> serverIP;

    playerMove initMsg;

    initMsg.moveType = 'X';
    initMsg.playerID = serverIP;
    initMsg.playerRoll = NULL;

	cout << "before client init" << endl;

	client GameClient(PORT, serverIP.c_str() );

    cout << "after client initialized" << endl;

    setup(argc, argv); // openGL setup
    while (GameClient.getSSM()->getCurrentState() != States::GAME_EXIT) {
        if (GameClient.getSSM()->getCurrentState() != States::GAME_SETUP) {
            GLRenderShared::board = GameClient.getPlayingBoard();
        }
    };
}