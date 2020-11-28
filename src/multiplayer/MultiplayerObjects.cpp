#include "iostream"
#include "MultiplayerObjects.h"

//Implementation for Multiplayer Classes

//Function that recieves player moves from

using namespace std;

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
            socket->state.input(inMsg); //Passes the message through the state machine
        }
    } while (true);
}
//Function that recieves board info from server
void clientReceive(client *socket)
{
    // Loop that waits on incoming messages
    boardInfo inMsg;
    sockaddr_in from;
    socklen_t fromlen{sizeof(struct sockaddr_in)};
    int n;
    do
    {
        n = recvfrom(socket->m_sockfd, (char *)&inMsg, sizeof(boardInfo), 0, (struct sockaddr *)&from, &fromlen);
        if (n < 0)
        {
            break;
        }
        else
        {
            socket->
        }
    } while (true);
}

/////////////////////////////////////////////////
// Server Implementation
/////////////////////////////////////////////////

// Cross-platform socket initialize

// Cross-platform socket initialize
server::server(unsigned short usPort) : portNum(usPort)
{
    sockaddr_in serv_addr;
    sockInit();
    // Create the socket
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
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

//Function to send player info the clients
void server::updateBoard(const std::string &strTo, unsigned short usPortNum, const boardInfo &players)
{
    struct hostent *client_entity;
    struct sockaddr_in client_addr;
    socklen_t fromlen;
    struct sockaddr_in from;
    client_entity = gethostbyname(strTo.c_str());
    if (client_entity == NULL)
    {
        fprintf(stderr, "Error, no such host\n");
    }
    memset((char)client_addr, sizeof(client_addr), 0);
    serv_addr.sin_family = AF_INET;
    memmove((char)&client_addr.sin_addr.s_addr, (char)client_entity->h_addr, client_entity->h_length);
    client_addr.sin_port = htons(usPortNum);
    fromlen = sizeof(from);
    if (connect(sockfd, (struct sockaddr) & client_addr, sizeof(client_addr)) < 0)
        error("ERROR connecting");
    int n = sendto(m_sockfd, (char)&players, sizeof(boardInfo), 0, (struct sockaddr) & client_addr, sizeof(client_addr));
    if (n < 0)
        error("ERROR writing to socket")
};

int server::sockInit(void)
{
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1, 1), &wsa_data);
#else
    return 0;
#endif
}

// Cross-platform socket quit
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

/////////////////////////////////////////////////
// Client Implementation
/////////////////////////////////////////////////

client::client(unsigned short usPort, char * addr) : portNum(usPort)
{
    //error checking for IP address length here
    string address = addr;  //Define the 
    sockaddr_in serv_addr;
    sockInit();
    // Create the socket
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // Make sure the socket was created
    if (m_sockfd < 0)
        error("ERROR opening socket");
    // Zero out the variable serv_addr
    memset((char *)&serv_addr, sizeof(serv_addr), 0);

    // Initialize the serv_addr
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = address;  // define IP address

    // Convert port number from host to network
    serv_addr.sin_port = htons(usPort);
    // Bind the socket to the port number
    if (bind(m_sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR on binding");
    }
    // Start thread that waits for messages

    recieveThread = std::thread(clientReceive, this);
};

//Function to send turn decisions to the server
void client::submitTurn(const std::string &strTo, unsigned short usPortNum, const playerMove &player)
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
    memset((*char)serv_addr, sizeof(serv_addr), 0);
    serv_addr.sin_family = AF_INET;
    memmove((*char)&serv_addr.sin_addr.s_addr, (char)server_entity->h_addr, server_entity->h_length);
    serv_addr.sin_port = htons(usPortNum);
    fromlen = sizeof(from);
    if (connect(sockfd, (struct sockaddr) & serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    int n = sendto(m_sockfd, (char)&player, sizeof(playerMove), 0, (struct sockaddr) & serv_addr, sizeof(serv_addr));
    if (n < 0)
        error("ERROR writing to socket")
};

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
