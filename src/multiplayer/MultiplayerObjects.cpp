/*
Authors: Christopher Kennedy, Jackson Stanhope, Jim O'Donnell, Michael Zhou Lu, Ruben Quiros, and Shelby Crisp 
Class: ECE 4122
Last Date Modified: 12/1/20
Description:
This is the implementation for the client and server classes function. A lot of the core of our code was taken from the skeleton code provided in lab 5. 
*/
#include <iostream>
#include <string.h>
#include <multiplayer/MultiplayerObjects.h>
#include <statemachine/StateMachine.h>
#include <builder/BoardFactory.h>
#include <stdlib.h>

//Implementation for Multiplayer Classes
//Function that recieves player moves from

using namespace std;

//This function is used to recieve information on the server
void serverReceive(server *socket)
{
    // Loop that waits on incoming messages
    playerMove inMsg;
    sockaddr_in from;
    socklen_t fromlen{sizeof(struct sockaddr_in)};
    int n;
    do
    {
        n = recvfrom(socket->m_sockfd, (char *)&inMsg, sizeof(playerMove), 0, (struct sockaddr *)&from, &fromlen);
        if (n < 0)
        {
            break;
        }
        else
        {
            std::cout << "Message from client recieved" << std::endl;
            socket->addSource(from);
            std::cout << "adding to source!" << std::endl;
            StateMachine *sm = socket->ssm;
            std::cout << "got the sm" << std::endl;
            if (!sm)
            {
                std::cout << "nullptr" << std::endl;
            }
            cout << "move pos " << inMsg.movePosition << endl;
            cout << "username: " << inMsg.playerID << endl;

            sm->input(inMsg); //Passes the message through the state machine
            std::cout << "updated statemachine" << std::endl;
        }
    } while (true);
}
//Function that recieves board info from server
void clientReceive(client *socket)
{
    // Loop that waits on incoming messages
    playerMove inMsg;
    sockaddr_in from;
    socklen_t fromlen{sizeof(struct sockaddr_in)};
    int n;
    do
    {
        n = recvfrom(socket->m_sockfd, (char *)&inMsg, sizeof(playerMove), 0, (struct sockaddr *)&from, &fromlen);
        if (n < 0)
        {
            break;
        }
        else
        {
            std::cout << "Message from server recieved" << std::endl;
            socket->ssm->ssmMutex.lock();
            socket->ssm->input(inMsg);
            socket->ssm->ssmMutex.unlock();
        }
    } while (true);
}

/////////////////////////////////////////////////
// Server Implementation
/////////////////////////////////////////////////

// Cross-platform socket initialize
server::server(unsigned short usPort)
{
    std::cout << "making server board." << std::endl;
    playingBoard = new Board("server_board");

    BoardFactory bf(playingBoard, 40);
    bf.makeBoard();
    std::cout << "setting statemachine to board" << std::endl;
    this->ssm = playingBoard->getSSM();
    this->ssm->setIsClient(false);

    portNum = usPort;
    sockaddr_in serv_addr;

    sockInit();

    // Create the socket
    m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    // Make sure the socket was created
    if (m_sockfd < 0)
        error("ERROR opening socket");

    // Zero out the variable serv_addr
    memset((char *)&serv_addr, sizeof(serv_addr), 0);

    // Initialize the serv_addr
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // Convert port number from host to network
    serv_addr.sin_port = htons(usPort);

    // Bind the socket to the port number
    if (bind(m_sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR on binding");
    }
    // Start thread that waits for messages
    recieveThread = std::thread(serverReceive, this);
};

// Function called to send info to all clients
void server::sendToClient(const playerMove &players)
{
    char buf[INET_ADDRSTRLEN];
    for (list<sockaddr_in>::iterator lst = sources.begin(); lst != sources.end(); lst++)
    {
        updateBoard(inet_ntop(AF_INET, &lst->sin_addr, buf, sizeof(buf)), htons(lst->sin_port), players);
    }
}

//Function to send player info the clients
void server::updateBoard(const std::string &strTo, unsigned short usPortNum, const playerMove &players)
{
    struct hostent *client_entity;
    struct sockaddr_in client_addr;
    client_entity = gethostbyname(strTo.c_str());
    if (client_entity == NULL)
    {
        cout << "Error, no such host";
        exit(0);
    }
    memset((char *)&client_addr, sizeof(client_addr), 0);
    client_addr.sin_family = AF_INET;
    memmove((char *)&client_addr.sin_addr.s_addr, (char *)client_entity->h_addr, client_entity->h_length);
    client_addr.sin_port = htons(usPortNum);
    int n = sendto(m_sockfd, (char *)&players, sizeof(playerMove), 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
    if (n < 0)
        error("ERROR writing to socket");
};

//Server Socket initalization
int server::sockInit(void)
{
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1, 1), &wsa_data);
#else
    return 0;
#endif
}

// Cross-platform server socket quit
int server::sockQuit(void)
{
#ifdef _WIN32
    return WSACleanup();
#else
    return 0;
#endif
}

// Cross-platform socket close
int server::sockClose()
{
    int status = 0;
#ifdef _WIN32
    status = shutdown(m_sockfd, SD_BOTH);
    if (status == 0)
    {
        status = closesocket(m_sockfd);
    }
#else
    status = shutdown(m_sockfd, SHUT_RDWR);
    if (status == 0)
    {
        status = close(m_sockfd);
    }
#endif

    // Set to show socket closed
    m_sockfd = -1;
    // Wait for thread to shut down.
    return status;
}

// Output error message and exit
void server::error(const char *msg)
{
    perror(msg);
    // Make sure any open sockets are closed before calling exit
    sockClose();
    exit(1);
}

//Function that adds a new source to the server function.
void server::addSource(const sockaddr_in &from)
{
    bool bIsPresent = false;
    // Iterate through list check is already present
    for (auto i : sources)
    {
        if (memcmp(&i, &from, sizeof(sockaddr_in)) == 0) //Compare blocks of memory
            bIsPresent = true;                           //If that block of memory contains the sockaddr_in then flip the bool
    }
    if (!bIsPresent)
    {
        sources.push_back(from); //Insert the sockaddr_in if it is not in the list
    }
}

void server::retroJoin() {
    std::cout << "sending a retro join msg" << std::endl;
    for (std::vector<playerMove>::iterator it = joinedPlayersMsg.begin(); it < joinedPlayersMsg.end(); it++) {
        std::cout << "here" << std::endl;
        sendToClient(*it);
    }
}

// definition of destructor needed ?? for some reason
server::~server(){};

/////////////////////////////////////////////////
// Client Implementation
/////////////////////////////////////////////////

//Constructor for the client object
client::client(unsigned int usPort, std::string addr)
{
    //error checking for IP address length here
    portNum = usPort;

    playingBoard = new Board("client_board");
    BoardFactory bf(playingBoard, 40);
    bf.makeBoard();

    this->server_address = addr;
    this->ssm = playingBoard->getSSM();
    this->ssm->setIsClient(true); // flag to indicate this is a client

    sockaddr_in client_addr;
    sockInit();
    cout << "After init" << endl;
    //playingBoard = Board("Client_Board");
    // Create the socket
    m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    // Make sure the socket was created
    cout << "Socket created" << endl;
    if (m_sockfd < 0)
        error("ERROR opening socket");
    // Zero out the variable serv_addr
    memset((char *)&client_addr, sizeof(client_addr), 0);
    //Initialize client address
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY;
    // Convert port number from host to network
    client_addr.sin_port = htons(usPort);
    // Bind the socket to the port number
    do
    {
        int randSocket = rand() % 30000 + 20000;
        client_addr.sin_port = htons(randSocket);
    } while (bind(m_sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0);

    // Start thread that waits for messages

    recieveThread = std::thread(clientReceive, this);
};

//Sends message to a server
void client::sendToServer(const playerMove &player)
{
    submitTurn(server_address, portNum, player);
}

//Function to send turn decisions to the server
void client::submitTurn(const std::string &strTo, unsigned int usPortNum, const playerMove &player)
{
    //Send playermove to server
    //THIS IS TCP, so in init, change SOCK_DGRAM to SOCK_STREAM
    struct hostent *server_entity;
    struct sockaddr_in serv_addr;
    socklen_t fromlen;
    struct sockaddr_in from;
    server_entity = gethostbyname(strTo.c_str());
    if (server_entity == NULL)
    {
        fprintf(stderr, "Error, no such host\n");
    }
    memset((char *)&serv_addr, sizeof(serv_addr), 0);
    serv_addr.sin_family = AF_INET;
    memmove((char *)&serv_addr.sin_addr.s_addr, (char *)server_entity->h_addr, server_entity->h_length);
    serv_addr.sin_port = htons(usPortNum);
    fromlen = sizeof(from);

    int n = sendto(m_sockfd, (char *)&player, sizeof(playerMove), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (n < 0)
        error("ERROR writing to socket");
};

//Client socket initalization
int client::sockInit(void)
{
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1, 1), &wsa_data);
#else
    return 0;
#endif
}

// Cross-platform socket quit
int client::sockQuit(void)
{
#ifdef _WIN32
    return WSACleanup();
#else
    return 0;
#endif
}

// Cross-platform socket close
int client::sockClose()
{

    int status = 0;

#ifdef _WIN32
    status = shutdown(m_sockfd, SD_BOTH);
    if (status == 0)
    {
        status = closesocket(m_sockfd);
    }
#else
    status = shutdown(m_sockfd, SHUT_RDWR);
    if (status == 0)
    {
        status = close(m_sockfd);
    }
#endif

    // Set to show socket closed
    m_sockfd = -1;
    // Wait for thread to shut down.
    return status;
}

// Output error message and exit
void client::error(const char *msg)
{
    perror(msg);
    // Make sure any open sockets are closed before calling exit
    sockClose();
    exit(1);
}

//Function that adds a new source to the server function.
void client::addSource(const sockaddr_in &from)
{
    bool bIsPresent = false;
    sources = from;
    // Iterate through list check is already present
}

//Returns the playing board for the client
Board *client::getPlayingBoard()
{
    return playingBoard;
}

client::~client(){};

//Returns the servers state machine
StateMachine *server::getSSM()
{
    return ssm;
}

//Returns the clients state machine
StateMachine *client::getSSM()
{
    return ssm;
}
