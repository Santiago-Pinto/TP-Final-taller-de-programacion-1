// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#ifndef _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_CLIENT_H_
#define _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_CLIENT_H_
//------------------------------------------------------------------------------
class ClientProxyGame;
class ClientPlayer;
//------------------------------------------------------------------------------
#include <cstddef>
#include <vector>
//------------------------------------------------------------------------------
class Client {
 public :
    //--------------------------------------------------------------------------
    Client();
    //--------------------------------------------------------------------------
    ~Client();
    //--------------------------------------------------------------------------
    void run();
    //--------------------------------------------------------------------------
    size_t welcomeInterface();
    //--------------------------------------------------------------------------
};
//------------------------------------------------------------------------------
#endif  // _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_CLIENT_H_
