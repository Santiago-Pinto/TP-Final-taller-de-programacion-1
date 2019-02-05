// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#ifndef _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERROAD_H_
#define _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERROAD_H_
//------------------------------------------------------------------------------
#include "serverRoadAsphaltRoad.h"
//------------------------------------------------------------------------------
class ServerRoad: public ServerRoadAsphaltRoad {
 public :
    //--------------------------------------------------------------------------
    ServerRoad(uint32_t x, uint32_t y);
    //--------------------------------------------------------------------------
    ~ServerRoad();
    //--------------------------------------------------------------------------
    virtual bool isLava()const;
    //--------------------------------------------------------------------------
    virtual bool isDust()const;
    //--------------------------------------------------------------------------
    virtual bool isGrass()const;
    //--------------------------------------------------------------------------
    virtual bool isSnow()const;
    //--------------------------------------------------------------------------
    virtual bool isWater()const;
    //--------------------------------------------------------------------------
    virtual bool isSwamp()const;
    //--------------------------------------------------------------------------
    virtual bool isRoad()const;
    //--------------------------------------------------------------------------
    virtual bool isAsphaltRoad()const;
    //--------------------------------------------------------------------------
};
//------------------------------------------------------------------------------
#endif  // _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERROAD_H_