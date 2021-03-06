// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#ifndef _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERTASKCREATEMML_H_
#define _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERTASKCREATEMML_H_
//------------------------------------------------------------------------------
class ServerGame;
//------------------------------------------------------------------------------
#include <ctime>
#include <string>
#include "serverTask.h"
//------------------------------------------------------------------------------
class ServerTaskCreateMML: public ServerTask {
 private :
    size_t idBuilding;
 public :
    //--------------------------------------------------------------------------
    ServerTaskCreateMML(ServerGame& aGame, size_t idBuilding);
    //--------------------------------------------------------------------------
    ~ServerTaskCreateMML();
    //--------------------------------------------------------------------------
    virtual void execute();
    //--------------------------------------------------------------------------
    virtual bool isRelocable()const;
    //--------------------------------------------------------------------------
};
//------------------------------------------------------------------------------
#endif  // _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERTASKCREATEMML_H_
