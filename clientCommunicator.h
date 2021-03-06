// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#ifndef _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_CLIENTCOMMUNICATOR_H_
#define _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_CLIENTCOMMUNICATOR_H_
//------------------------------------------------------------------------------
class Socket;
class ClientProxyGame;
class ClientPlayer;
//------------------------------------------------------------------------------
#include <cstddef>
#include <queue>
#include <string>
#include "commonThreads.h"
#include "commonParser.h"
#include "commonQueue.h"
//------------------------------------------------------------------------------
#define BUF_LEN_SEND 330
//------------------------------------------------------------------------------
typedef commonQueue<std::string> petitions_t;
//------------------------------------------------------------------------------
class ClientCommunicator: public Thread {
 public :
    bool finish;
 private:
    Socket& socket;
    petitions_t& petitions;
    ClientProxyGame& proxyGame;
    ClientPlayer& aPlayer;
    Parser aParser;
    char buffer[BUF_LEN_SEND];
    std::string message;
    char* port = const_cast<char*>("8080");
    char* host = const_cast<char*>("127.0.0.1");
 public :
    //--------------------------------------------------------------------------
    ClientCommunicator(
            Socket& socket, petitions_t& petitions, ClientProxyGame& proxyGame,
            ClientPlayer& aPlayer);
    //--------------------------------------------------------------------------
    ~ClientCommunicator();
    //--------------------------------------------------------------------------
    void run();
    //--------------------------------------------------------------------------
    void sendMessage(std::string command);
    //--------------------------------------------------------------------------
    void receiveMessage();
    //--------------------------------------------------------------------------
    void stop();
    //--------------------------------------------------------------------------
    void getMessage();
    //--------------------------------------------------------------------------
    bool gameOver(std::string message);
    //--------------------------------------------------------------------------
};
//------------------------------------------------------------------------------
#endif  // _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_CLIENTCOMMUNICATOR_H_
