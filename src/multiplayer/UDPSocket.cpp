#include <multiplayer/UDPSocket.h>
#include <multiplayer/MultiplayerObjects.h>
#include <iostream>

using namespace std;



void serverReceive(ECE_UDPSocket* socket)
{
    // Loop that waits on incoming messages
    playerMove inMsg;
    sockaddr_in from;
    socklen_t fromlen{sizeof(struct sockaddr_in)};
    int n;
    do
    {
        n = recvfrom(socket->m_sockfd, (char *)&inMsg, sizeof(playerMove), 0, (struct sockaddr *)&from, &fromlen);
        if (n < 0) {
            break;
        }
        else {
            std::cout << "Message from client recieved" << std::endl;
            socket->addSource(from);
            socket->ssm->input(inMsg); //Passes the message through the state machine
        } 
    } while (true);
}

//Function that recieves board info from server
void clientReceive(ECE_UDPSocket* socket)
{
    // Loop that waits on incoming messages
    playerMove inMsg;
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
            std::cout << "Message from server recieved" << std::endl;
            socket->ssm->input(inMsg);
        }
    } while (true);
}

// INIT SOCKET 
ECE_UDPSocket::ECE_UDPSocket(unsigned short usPort) : m_usPort(usPort)  // if you bind to a port number 0, system interprets that as whatever port is available
{
    sockaddr_in serv_addr;
    sockInit();
    
    m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // Create the socket.  params:  ipv4, UDP, ip protocol (0)
    
    if (m_sockfd < 0)  // Make sure the socket was created.  -1 is failure
        error("ERROR opening socket");
    
    memset((char*)&serv_addr, sizeof(serv_addr), 0);  // Zero out the variable serv_addr
    // memset --> set values for large sets of memory. params: address in memory, size of the variable, any byte value (0-255)

    // Initialize the serv_addr.  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // Convert port number from host to network
    serv_addr.sin_port = htons(usPort); // htons = host to network (short).  what system am i on & what endianness, convert to that endianness
    // BYTE ORDERING IS IMPORTANT.  BIG ENDIAN VS. LITTLE ENDIAN

    if (bind(m_sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)  // Bind the socket to the port number
    {
        error("ERROR on binding");
    }

    // Start thread that waits for messages 
    m_recvThread = std::thread(receiveSocketMsgs, this); // create thread to listen for messages for each new socket
}

ECE_UDPSocket::~ECE_UDPSocket()  // probably need to add thread join 
{
    if (m_sockfd > 0)
        sockClose();
}

void ECE_UDPSocket::addSource(const sockaddr_in& from) // this is called from receiveSocketMsgs
// iterate through std::list<sockaddr_in> m_lstSources to compare existing sources with source passed to addSource
{
    bool bIsPresent = false;
    // Iterate through list check is already present

    for (sockaddr_in& source : m_lstSources) 
        // for each source in the m_lstSources list, compare the IPv4 address to the IPv4 address passed into addSource. 
        // if it already exists, ignore it; if not, add it to the list
    {
        if (ntohl(source.sin_addr.s_addr) == ntohl(from.sin_addr.s_addr) && ntohs(source.sin_port) == ntohs(from.sin_port)) // do i need to compare the port too???? not sure. s_addr = ulong, sin_port = ushort
            // https://docs.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-sockaddr_in
        {
            bIsPresent = true; // set this true if the address is found
        }
    }

    if (!bIsPresent) // if address wasn't found, add it to the m_lstSources list
    {
        // add source to list
        m_mutex.lock();
        m_lstSources.push_back(from); // if address is not found in list, add it to the list
        m_mutex.unlock();
    }
}

void ECE_UDPSocket::sendMessage(const std::string& strTo, unsigned short usPortNum, const udpMessage& msg) 
{
    struct hostent* server;
    struct sockaddr_in serv_addr;
    socklen_t fromlen;
    struct sockaddr_in from;

    server = gethostbyname(strTo.c_str());

    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    // Zero out serv_addr variable
    memset((char*)&serv_addr, sizeof(serv_addr), 0);

    serv_addr.sin_family = AF_INET;

    memmove((char*)&serv_addr.sin_addr.s_addr, (char*)server->h_addr, server->h_length);

    serv_addr.sin_port = htons(usPortNum);

    fromlen = sizeof(from);

    int n = sendto(m_sockfd, (char*)&msg, sizeof(udpMessage), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    if (n < 0)
        error("ERROR writing to socket");
}

/////////////////////////////////////////////////
// Cross-platform socket initialize
int ECE_UDPSocket::sockInit(void)
{
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1, 1), &wsa_data);
#else
    return 0;
#endif
}
/////////////////////////////////////////////////
// Cross-platform socket quit
int ECE_UDPSocket::sockQuit(void)
{
#ifdef _WIN32
    return WSACleanup();
#else
    return 0;
#endif
}
/////////////////////////////////////////////////
// Cross-platform socket close
int ECE_UDPSocket::sockClose()
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
/////////////////////////////////////////////////
// Output error message and exit
void ECE_UDPSocket::error(const char* msg)
{
    perror(msg);
    // Make sure any open sockets are closed before calling exit
    exit(1);
}