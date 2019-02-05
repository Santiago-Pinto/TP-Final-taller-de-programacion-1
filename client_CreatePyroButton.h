#ifndef CLIENT_CREATEPYROBUTTON_H_INCLUDED
#define CLIENT_CREATEPYROBUTTON_H_INCLUDED
//------------------------------------------------------------------------------
#include "client_Frame.h"
#include "client_Button.h"
#include "clientProxyGame.h"

//------------------------------------------------------------------------------
class ClientCreatePyroButton: public ClientButton {
 public :
    //--------------------------------------------------------------------------
    ClientCreatePyroButton(
            unsigned int id, unsigned int pos_x, unsigned int pos_y);
    //--------------------------------------------------------------------------
    void handle_click(ClientProxyGame &proxyGame);
    //--------------------------------------------------------------------------
};
#endif // CLIENT_CREATEPYROBUTTON_H_INCLUDED
