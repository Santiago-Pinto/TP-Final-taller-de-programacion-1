// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#ifndef _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERSTATESTILL_H_
#define _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERSTATESTILL_H_
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#include <ctime>
#include <string>
#include "serverState.h"
//------------------------------------------------------------------------------
class ServerStateStill: public ServerState {
 public :
    //--------------------------------------------------------------------------
    ServerStateStill();
    //--------------------------------------------------------------------------
    ~ServerStateStill();
    //--------------------------------------------------------------------------
    virtual bool isMoving()const;
    //--------------------------------------------------------------------------
    virtual bool isAttackingUnit()const;
    //--------------------------------------------------------------------------
    virtual bool isAttackingObject()const;
    //--------------------------------------------------------------------------
    virtual bool isStill()const;
    //--------------------------------------------------------------------------
    virtual bool isDead()const;
    //--------------------------------------------------------------------------
    virtual bool isBroken()const;
    //--------------------------------------------------------------------------
};
//------------------------------------------------------------------------------
#endif  // _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERSTATESTILL_H_
