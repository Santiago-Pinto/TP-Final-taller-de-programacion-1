// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#ifndef _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERBRIDGES_H_
#define _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERBRIDGES_H_
//------------------------------------------------------------------------------
#include <vector>
#include <string>
#include "serverObject.h"
//------------------------------------------------------------------------------
class ServerBridges: public ServerObject {
 public :
    //--------------------------------------------------------------------------
    ServerBridges(ServerNode& position, size_t id);
    //--------------------------------------------------------------------------
    ~ServerBridges();
    //--------------------------------------------------------------------------
    virtual bool canPassThrough() const;
    //--------------------------------------------------------------------------
    virtual void addObjectToNodes(ServerMap& aMap);
    //--------------------------------------------------------------------------
    virtual bool isBuilding()const;
    //--------------------------------------------------------------------------
    virtual bool isFort()const;
    //--------------------------------------------------------------------------
    virtual bool isVehicleFactorie()const;
    //--------------------------------------------------------------------------
    virtual bool isRobotFactorie()const;
    //--------------------------------------------------------------------------
    virtual bool isFlag()const;
    //--------------------------------------------------------------------------
    virtual bool isStone()const;
    //--------------------------------------------------------------------------
    virtual bool isIceBlock()const;
    //--------------------------------------------------------------------------
    virtual bool isBridge()const;
    //--------------------------------------------------------------------------
    virtual bool isWoodenBridge()const = 0;
    //--------------------------------------------------------------------------
    virtual bool isConcreteBridge()const = 0;
    //--------------------------------------------------------------------------
};
//------------------------------------------------------------------------------
#endif  // _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERBRIDGES_H_
