//This file is going to be the core of the multiplayer server.
//Running this program will begin the server.
//Some of the functions below were found at:https://www.geeksforgeeks.org/c-program-display-hostname-ip-address/

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
#include <MultiplayerObjects.h>
#include <Player.h>

#define PORT 6500

// Returns hostname for the local computer
void checkHostName(int hostname)
{
    if (hostname == -1)
    {
        perror("gethostname");
        exit(1);
    }
}

// Returns host information corresponding to host name
void checkHostEntry(struct hostent *hostentry)
{
    if (hostentry == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }
}

// Converts space-delimited IPv4 addresses
// to dotted-decimal format
void checkIPbuffer(char *IPbuffer)
{
    if (NULL == IPbuffer)
    {
        perror("inet_ntoa");
        exit(1);
    }
}

// Driver code
int main()
{
    char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;
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
    IPbuffer = inet_ntoa(*((struct in_addr *)host_entry->h_addr_list[0]));
    std::cout << IPbuffer << std::endl;
    server GameServer(PORT);
    char player1_IP[INET_ADDRSTRLEN];
    char player2_IP[INET_ADDRSTRLEN];
    do
    { //Loop to wait for both clients to connect
        if (GameServer.sources.size() == 2)
        {
            break;
        }
    } while (true);
    
    inet_ntop(AF_INET, &(GameServer.sources.at(0).sin_addr), player1_IP, INET_ADDRSTRLEN);  //Gets IP of the first player
    inet_ntop(AF_INET, &(GameServer.sources.at(1).sin_addr), player2_IP, INET_ADDRSTRLEN);  //Gets IP of the second player
    string name1= player1_IP;           //Define the name for player 1 based on the IP address
    string name2= player2_IP;           //Define the name for player 2 based on the IP address
    Player p1(name1);                     //Instantiate Player 1
    Player p2(name2);                     //Instantiate Player 2
    GameServer.players[0] = p1;    //Define player 1 object based on the IP address
    GameServer.players[1] = p2;    //Define player 2 object based on the IP address
    do
    { //Loop that the game

    } while (true);
}