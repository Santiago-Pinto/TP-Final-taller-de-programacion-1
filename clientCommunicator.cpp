// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#include <netinet/in.h>
#include <string>
#include <vector>
#include <stdint-gcc.h>
#include "clientCommunicator.h"
#include "clientProxyGame.h"
#include "commonSocket.h"
#include "clientPlayer.h"
#include "commonException.h"
//------------------------------------------------------------------------------
#define END "end"
#define DELIM '-'
#define GET_MODEL "getModel"
#define GET_INITIAL_MODEL "getInitialModel"
#define CREATE_PLAYER "createPlayer"
#define WINNER "winner"
//------------------------------------------------------------------------------
// CLIENT COMMUNICATOR CONSTRUCTOR
//------------------------------------------------------------------------------
ClientCommunicator::ClientCommunicator(
        Socket& socket, petitions_t& petitions, ClientProxyGame& proxyGame,
        ClientPlayer& aPlayer):
        socket(socket), petitions(petitions), proxyGame(proxyGame),
        aPlayer(aPlayer) {
    finish = false;
    socket.socketCreateAndConnect(host, port);
}
//------------------------------------------------------------------------------
// CLIENT COMMUNICATOR DESTRUCTOR
//------------------------------------------------------------------------------
ClientCommunicator::~ClientCommunicator() {}
//------------------------------------------------------------------------------
// RUN
//------------------------------------------------------------------------------
void ClientCommunicator::run() {
    std::vector<std::string> parsedMessage;
    while (!finish) {
        if (finish) break;
        std::string command = petitions.pop();
        sendMessage(command);
        if (command == GET_INITIAL_MODEL) {
            getMessage();
            aPlayer.charged = true;
            if (finish) break;
        } else if (command == GET_MODEL) {
            getMessage();
            if (finish) break;
        } else {
            parsedMessage = aParser.parseLine(command, DELIM);
            if (parsedMessage[0] == CREATE_PLAYER) {
                receiveMessage();
                if (finish) break;
                size_t idPlayer = aParser.stringToSize_t(message);
                aPlayer.setIdPlayer(idPlayer);
            }
        }
    }
    finish = true;
    socket.socketShutdown(SHUT_RDWR);
}
//------------------------------------------------------------------------------
// SEND MESSAGE
//------------------------------------------------------------------------------
void ClientCommunicator::sendMessage(std::string command) {
    if (command.size() == 0) return;
    uint32_t length = htonl((uint32_t)command.size());
    socket.socketSend(reinterpret_cast<char*>(&length), 4);
    socket.socketSend(command.c_str(), command.size());
}
//------------------------------------------------------------------------------
// RECEIVE MESSAGE
//------------------------------------------------------------------------------
void ClientCommunicator::receiveMessage() {
    message.clear();
    size_t bytes, size;
    uint32_t length;
    bytes = socket.socketReceive(reinterpret_cast<char*>(&length), 4);
    size = ntohl(length);
    if (bytes == 0) {
        finish = true;
        return;
    }
    socket.socketReceive(buffer, size);
    message = aParser.bufferToString(buffer, size);
}
//------------------------------------------------------------------------------
// STOP
//------------------------------------------------------------------------------
void ClientCommunicator::stop() {
    finish = true;
    join();
}
//------------------------------------------------------------------------------
// GET MESSAGE
//------------------------------------------------------------------------------
void ClientCommunicator::getMessage() {
    message.clear();
    receiveMessage();
    while (message != END) {
        if (gameOver(message)) return;
        proxyGame.receiveModel(message);
        receiveMessage();
    }
    proxyGame.checkNotUpdatedModel();
}
//------------------------------------------------------------------------------
// GAME OVER
//------------------------------------------------------------------------------
bool ClientCommunicator::gameOver(std::string message) {
    std::vector<std::string> parsedMessage;
    parsedMessage = aParser.parseLine(message, DELIM);
    if (parsedMessage[0] == WINNER) {
        size_t winnerId = aParser.stringToSize_t(parsedMessage[1]);
        printf("THE TEAM %zu HAS WON\n", winnerId);
        finish = true;
        bool victory = winnerId == aPlayer.getIdTeam();
        aPlayer.aMap.showOutcome(victory, aPlayer.screen);
        return true;
    }
    return false;
}
//------------------------------------------------------------------------------
