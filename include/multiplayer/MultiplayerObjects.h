
//Structure that is used to define player attributes
struct playerInfo{
    unsigned char playerNum;    //defines which player is which
    int money;                  //Changes in money
    int boardNum;               //Space indicator
    int turnCounter;
    bool isTurn;
}

//Determines the move that each player makes
struct playerMove{
    unsigned char moveChoice;    //Selects which move
}

//Message sent to 
struct boardInfo{
    unsigned char playerCount;  //Indicator as to how many players there are in the game
    char [4*sizeof(playerInfo)]; //Array of players information
}

//Class defined for each player
class server
{
public:
    server() = delete;
    ~server();
    server(unsigned short usPort);
    void updateBoard(const std::string &strTo, unsigned short usPortNum, const playerInfo &player);
    void addSource(const sockaddr_in &from); 
    int sockInit(void);
    int sockQuit(void);
    int sockClose();
    void error(const char *msg);
    int m_sockfd;

private:
    unsigned short portNum;
    std::thread recieveThread;  //Thread to receive board info
    std::vector<playerInfo> players;
    std::list<sockaddr_in> sources;
    std::mutex currTurn;
};

//Class defined for each player
class client
{
public:
    client() = delete;
    ~client();
    client(unsigned short usPort);
    void submitTurn(const std::string &strTo, unsigned short usPortNum, const playerMove &player);
    void addSource(const sockaddr_in &from); 
    int sockInit(void);
    int sockQuit(void);
    int sockClose();
    void error(const char *msg);
    int m_sockfd;

private:
    unsigned short portNum;
    std::thread recieveThread;
    std::vector<playerInfo> players;
    sockaddr_in sources;
    std::mutex currTurn;
};
