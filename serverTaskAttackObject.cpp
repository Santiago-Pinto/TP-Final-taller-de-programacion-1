// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#include "serverTaskAttackObject.h"
#include "serverGame.h"
#include "serverUnit.h"
#include "serverObject.h"
#include "serverStateAttackingUnit.h"
#include "serverArmament.h"
#include "serverStateBroken.h"
//------------------------------------------------------------------------------
// SERVER TASK ATTACK GROUNDOBJECT CONSTRUCTOR
//------------------------------------------------------------------------------
ServerTaskAttackObject::ServerTaskAttackObject(
        ServerGame& aGame, size_t idMunition, size_t idTarget):
        ServerTask::ServerTask(aGame), idMunition(idMunition),
        idTarget(idTarget) {
}
//------------------------------------------------------------------------------
// SERVER TASK ATTACK GROUNDOBJECT DESTRUCTOR
//------------------------------------------------------------------------------
ServerTaskAttackObject::~ServerTaskAttackObject() {}
//------------------------------------------------------------------------------
// IS RELOCABLE
//------------------------------------------------------------------------------
bool ServerTaskAttackObject::isRelocable() const {
    return false;
}
//------------------------------------------------------------------------------
// EXECUTE
//------------------------------------------------------------------------------
void ServerTaskAttackObject::execute() {
    ServerArmament* munition = aGame.getMunition(idMunition);
    ServerObject* receiver = aGame.gameMap.getObject(idTarget);
    munition->attack(*receiver);
    munition->changeState(*new ServerStateBroken());
}
//------------------------------------------------------------------------------
