// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#include <iostream>
#include <utility>
#include "serverArmament.h"
#include "serverObject.h"
#include "serverStateBroken.h"
#include "serverStateStill.h"
#include "serverNode.h"
#include "serverFort.h"
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// OBJECT CONSTRUCTOR
//------------------------------------------------------------------------------
ServerObject::ServerObject(ServerNode& position, size_t id):
        principalPosition(position), id(id) {
    damageReceived = 0;
    currentState = new ServerStateStill;
    wasAdded = false;
}
//------------------------------------------------------------------------------
// OBJECT DESTRUCTOR
//------------------------------------------------------------------------------
ServerObject::~ServerObject() {
    delete currentState;
}
//------------------------------------------------------------------------------
// IS BROKEN
//------------------------------------------------------------------------------
bool ServerObject::isBroken() const {
    return damageReceived >= structurePoints;
}
//------------------------------------------------------------------------------
// RECEIVED DAMAGE
//------------------------------------------------------------------------------
void ServerObject::receivedDamage(const ServerArmament& anArmament) {
    if (isBroken()) return;
    damageReceived += anArmament.getDamage();
    if (isBroken()) {
        changeState(*new ServerStateBroken());
    }
}
//------------------------------------------------------------------------------
// GET CURRENT STATE
//------------------------------------------------------------------------------
const ServerState* ServerObject::getCurrentState() const {
     return currentState;
}
//------------------------------------------------------------------------------
// CHANGE STATE
//------------------------------------------------------------------------------
void ServerObject::changeState(const ServerState& newState) {
    delete currentState;
    currentState = &newState;
}
//------------------------------------------------------------------------------
// GET ID
//------------------------------------------------------------------------------
const size_t& ServerObject::getId() const {
    return id;
}
//------------------------------------------------------------------------------
// GET WALKABLE NODE
//------------------------------------------------------------------------------
ServerNode* ServerObject::getWalkableNode() {
    for (ServerNode* node : positions) {
        for (ServerNode* anAdjacent : node->getAdjacent()) {
            if (anAdjacent->hasAGroundObject()) {
                if (!anAdjacent->getGroundObject()->canPassThrough()) {
                    continue;
                }
            }
            if (!anAdjacent->vehiclePassThrough()) continue;
            if (!anAdjacent->robotPassThrough()) continue;
            return anAdjacent;
        }
    }
    throw Exception("The walkable node of the ground object returned null\n");
}
//------------------------------------------------------------------------------
// HAS AN OWNER
//------------------------------------------------------------------------------
bool ServerObject::hasAnOwner() const {
    return getOwner() != nullptr;
}
//------------------------------------------------------------------------------
// GET OWNER
//------------------------------------------------------------------------------
const ServerPlayer* ServerObject::getOwner() const {
    return principalPosition.getOwner();
}
//------------------------------------------------------------------------------
// GET PRINCIPAL POSITION
//------------------------------------------------------------------------------
const ServerNode& ServerObject::getPrincipalPosition() const {
    return principalPosition;
}
//------------------------------------------------------------------------------
// WAS ADDED ON NODE
//------------------------------------------------------------------------------
bool ServerObject::wasAddedOnNode() const {
    return wasAdded;
}
//------------------------------------------------------------------------------
