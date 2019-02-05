#ifndef CLIENT_CREATEBUTTON_H_INCLUDED
#define CLIENT_CREATEBUTTON_H_INCLUDED
//------------------------------------------------------------------------------
#include <vector>
#include "client_Frame.h"
#include "client_Button.h"
#include "clientProxyGame.h"

//------------------------------------------------------------------------------
class ClientCreateButton: public ClientButton {
 public :
    //--------------------------------------------------------------------------
    ClientCreateButton(unsigned int id, unsigned int pos_x,unsigned int pos_y);
    //--------------------------------------------------------------------------
    void handle_click(ClientProxyGame &proxyGame);
    //--------------------------------------------------------------------------
};
#endif // CLIENT_CREATEBUTTON_H_INCLUDED
