#ifndef CLIENT_CREATETOUGHBUTTON_H_INCLUDED
#define CLIENT_CREATETOUGHBUTTON_H_INCLUDED
//------------------------------------------------------------------------------
#include "client_Frame.h"
#include "client_Button.h"
#include "clientProxyGame.h"

//------------------------------------------------------------------------------
class ClientCreateToughButton: public ClientButton {
 public :
    //--------------------------------------------------------------------------
    ClientCreateToughButton(
            unsigned int id, unsigned int pos_x, unsigned int pos_y);
    //--------------------------------------------------------------------------
    void handle_click(ClientProxyGame &proxyGame);
    //--------------------------------------------------------------------------
};
#endif // CLIENT_CREATETOUGHBUTTON_H_INCLUDED
