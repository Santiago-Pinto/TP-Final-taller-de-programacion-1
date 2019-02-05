#ifndef CLIENT_BUTTON_H_INCLUDED
#define CLIENT_BUTTON_H_INCLUDED
//------------------------------------------------------------------------------
#include <vector>
#include "client_Frame.h"
#include "client_GameObject.h"
#include "client_Camera.h"
#include "clientProxyGame.h"

//------------------------------------------------------------------------------
class ClientButton: public GameObject{
 protected :
    bool visible;
    std::vector<Frame> frames;
 public :
    //--------------------------------------------------------------------------
    ClientButton(unsigned int id, unsigned int pos_x, unsigned int pos_y);
    //--------------------------------------------------------------------------
    ~ClientButton();
    //--------------------------------------------------------------------------
    virtual void handle_click(ClientProxyGame& proxyGame) = 0;
    //--------------------------------------------------------------------------
    void draw(SDL_Surface* screen, ClientCamera& camera);
    //--------------------------------------------------------------------------
    void show();
    //--------------------------------------------------------------------------
    void hide();
    //--------------------------------------------------------------------------
};
#endif  // CLIENT_BUTTON_H_INCLUDED
