/*
Authors: Christopher Kennedy, Jackson Stanhope, Jim O'Donnell, Michael Zhou Lu, Ruben Quiros, and Shelby Crisp 
Class: ECE 4122
Last Date Modified: 12/1/20
Description:
This is the header file for the multiplayer class. 
*/

#ifndef MULTIPLAYER_OBJ_H
#define MULTIPLAYER_OBJ_H

#include <thread>
#include <list>
#include <string>
#include <mutex>
#include <gamerules/Player.h>
#include <gamerules/Board.h>
 
class StateMachine;

#ifdef _WIN32
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#ifndef _WIN32_WINNT
//   #define _WIN32_WINNT 0x0501  /* Windows XP. */
#endif
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */

typedef int SOCKET;
#endif

//Structure that is used to define player attributes
/* unsure if being used.
struct playerInfo
{
    unsigned char playerNum[15]; //defines which player is which
    int money;                   //Changes in money
    int boardNum;                //Space indicator
    int turnCounter;             //Indicates how many turns have been completed for each player
    bool isTurn;                 //Indicates whether it is this persons turn or not
};
*/ 

//Determines the move that each player makes
struct playerMove // CLIENT TO SERVER
{
    char playerID[5]; //ID that tells the server which turn is which
	int movePosition;  // space ID
	unsigned char moveType;  //Determines the move type
    unsigned int playerRoll; // the number that the player rolled
};

//Class defined for each player
class server {
public:
    server() = delete; //Deletes the server
    ~server();	//Destructor for the server
    server(unsigned short usPort);	//Constructor for the server
    void sendToClient(const playerMove& players);	//Sends the playermove struct to the client
    void updateBoard(const std::string &strTo, unsigned short usPortNum, const playerMove &players); //Function to send player info the clients
    void addSource(const sockaddr_in &from);	//Adds a new source to the sources list on the server
    int sockInit(void);	//Initilzes the server socket
    int sockQuit(void);	//Quits the server socket
    int sockClose();	//Closes the socket
    void error(const char *msg);	//Used for error handling 
    int m_sockfd; //Integer that stores the socket num
    StateMachine* getSSM();	//Returns a pointer to the statemachine
    std::vector<playerMove> joinedPlayersMsg;
    void retroJoin();

    friend void serverReceive(server *socket);	//Friend function to recieve server info

private:
    unsigned short portNum;	//Port number for that socket
    Board* playingBoard;	//Board pointer for the servers playing board
    std::thread recieveThread;   //Thread to receive board info
    std::list<sockaddr_in> sources;	//List of sources
    std::mutex currTurn;	//Mutex for the server
    StateMachine *ssm;		//Statemachine for the server
};	

//Class defined for each player
class client
{
public:
    client() = delete;	
    ~client();	//Destructor
    client(unsigned int usPort, std::string addr);	//Constructor for the client
    void submitTurn(const std::string &strTo, unsigned int usPortNum, const playerMove &player); //Function to send turn decisions to the server
    void addSource(const sockaddr_in &from);	//Adds a source to the socket
    void sendToServer(const playerMove &player);	//Sends the message "playerMove" to the server
    int sockInit(void);	//Initilzes the socket
    int sockQuit(void);	//QUits the socket
    int sockClose();	//Closes the socket
    void error(const char *msg);	//Error handling
    int m_sockfd;		//int for the client socket
    std::string server_address;	//String that holds the servers address
    StateMachine* getSSM();	//Returns a pointer to the state machine
    friend void clientReceive(client* socket);	//Function for recieving info from the server
    Board* getPlayingBoard();	//Returns a pointer to the board

private:
    unsigned int portNum;	//Port number for the clients
    Board* playingBoard;	//Pointer to the playing board	
    std::thread recieveThread;	//Thread for recieving info 
    sockaddr_in sources;	//A source for the server
    std::mutex currTurn;	//Mutex for a given turn
    StateMachine *ssm;		//Statemachine for the client
};

#endif
