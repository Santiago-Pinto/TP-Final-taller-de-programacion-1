// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#include <iostream>
#include "commonException.h"
#include "server.h"
//------------------------------------------------------------------------------
#define SUCCESS 0
#define ERROR 1
//------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------
int main() try {
    Server aServer;
    aServer.mainLoop();
    return SUCCESS;
} catch (const Exception& e) {
    printf("%s", e.what());
    return ERROR;
}
//------------------------------------------------------------------------------
