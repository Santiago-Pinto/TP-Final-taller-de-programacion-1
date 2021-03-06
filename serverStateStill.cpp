// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#include "serverStateStill.h"
//------------------------------------------------------------------------------
// SERVER STATE STILL CONSTRUCTOR
//------------------------------------------------------------------------------
ServerStateStill::ServerStateStill() {}
//------------------------------------------------------------------------------
// SERVER STATE STILL DESTRUCTOR
//------------------------------------------------------------------------------
ServerStateStill::~ServerStateStill() {}
//------------------------------------------------------------------------------
// IS MOVING
//------------------------------------------------------------------------------
bool ServerStateStill::isMoving() const {
    return false;
}
//------------------------------------------------------------------------------
// IS ATTACKING UNIT
//------------------------------------------------------------------------------
bool ServerStateStill::isAttackingUnit() const {
    return false;
}
//------------------------------------------------------------------------------
// IS ATTACKING OBJECT
//------------------------------------------------------------------------------
bool ServerStateStill::isAttackingObject() const {
    return false;
}
//------------------------------------------------------------------------------
// IS STILL
//------------------------------------------------------------------------------
bool ServerStateStill::isStill() const {
    return true;
}
//------------------------------------------------------------------------------
// IS DEAD
//------------------------------------------------------------------------------
bool ServerStateStill::isDead() const {
    return false;
}
//------------------------------------------------------------------------------
// IS BROKEN
//------------------------------------------------------------------------------
bool ServerStateStill::isBroken() const {
    return false;
}
//------------------------------------------------------------------------------
