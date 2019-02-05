// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#ifndef _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERVEHICLE_H_
#define _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERVEHICLE_H_
//------------------------------------------------------------------------------
class ServerNode;
//------------------------------------------------------------------------------
#include <cstddef>
#include "serverUnit.h"
//------------------------------------------------------------------------------
class ServerVehicle : public ServerUnit {
 protected :
    float baseSpeed;
 public :
    //--------------------------------------------------------------------------
    ServerVehicle(const ServerNode& initialPosition, size_t id);
    //--------------------------------------------------------------------------
    virtual ~ServerVehicle();
    //--------------------------------------------------------------------------
    float getBaseSpeed()const;
    //--------------------------------------------------------------------------
    virtual double getCost(const ServerNode& aNode);
    //--------------------------------------------------------------------------
    virtual double getSpeed(const ServerNode& aNode) const;
    //--------------------------------------------------------------------------
    virtual bool canPassThrough(const ServerNode &aNode) const;
    //--------------------------------------------------------------------------
    virtual bool isGrunt()const = 0;
    //--------------------------------------------------------------------------
    virtual bool isTough()const = 0;
    //--------------------------------------------------------------------------
    virtual bool isSniper()const = 0;
    //--------------------------------------------------------------------------
    virtual bool isPsycho()const = 0;
    //--------------------------------------------------------------------------
    virtual bool isPyro()const = 0;
    //--------------------------------------------------------------------------
    virtual bool isLaser()const = 0;
    //--------------------------------------------------------------------------
    virtual bool isJeep()const = 0;
    //--------------------------------------------------------------------------
    virtual bool isMML()const = 0;
    //--------------------------------------------------------------------------
    virtual bool isLightTank()const = 0;
    //--------------------------------------------------------------------------
    virtual bool isMediumTank()const = 0;
    //--------------------------------------------------------------------------
    virtual bool isHeavyTank()const = 0;
    //--------------------------------------------------------------------------
    virtual bool isVehicle()const;
    //--------------------------------------------------------------------------
    virtual bool isRobot()const;
    //--------------------------------------------------------------------------
 protected :
    //--------------------------------------------------------------------------
    float getDamageVehicleRel() const;
    //--------------------------------------------------------------------------
};
//------------------------------------------------------------------------------
#endif  // _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERVEHICLE_H_
