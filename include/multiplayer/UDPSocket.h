#pragma once

#include <thread>
#include <list>
#include <string>
#include <mutex>
#include <cstring>

#ifdef _WIN32  // this is defining what code to run if the OS is windows (_WIN32 is always defined for windows)
    /* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
    #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0501  /* Windows XP. */
    #endif
    #include <winsock2.h>
    #include <Ws2tcpip.h>

    #pragma comment (lib, "Ws2_32.lib")
#else  // code to use if OS is not windows 
    /* Assume that any non-Windows platform uses POSIX-style sockets instead. */
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
    #include <unistd.h> /* Needed for close() */

    typedef int SOCKET;
#endif

struct udpMessage
{
    unsigned short nVersion;  // htons()
    unsigned short nType;     // htons()
    unsigned short nMsgLen;   // htons()  message length
    unsigned long lSeqNum;    // htonl()  sequence number
    char chMsg[1000];
};

class ECE_UDPSocket
{
public:
    ECE_UDPSocket() = delete;  // removing default contructor.  prevents class from being created without a port number
    ~ECE_UDPSocket();
    ECE_UDPSocket(unsigned short usPort);

	void serverReceive(server *socket);
	void clientReceive(client *socket);

	bool getNextMessage(udpMessage& msg);

    void sendMessage(const std::string& strTo, unsigned short usPortNum, const udpMessage& msg);
    void clearCompositeMsg();
    void displayCompositeMsg();
    // Other stuff
    void sendCompositeMsg();
    void processMessage(const udpMessage &inMsg); // Add msg to the list
    void addSource(const sockaddr_in &from); // Add source to the list

    int sockInit(void); // initialize socket
    int sockQuit(void); // have to close sockets
    int sockClose();
    void error(const char* msg);


    int m_sockfd;
private:
    unsigned short m_usPort;
    std::thread m_recvThread;
    std::list<udpMessage> m_lstMsgs;
    std::list<sockaddr_in> m_lstSources;
    std::mutex m_mutex;
};