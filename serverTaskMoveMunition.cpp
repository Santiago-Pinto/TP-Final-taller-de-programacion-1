// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#include "serverTaskMoveMunition.h"
#include "serverGame.h"
#include "serverPlayer.h"
#include "serverNode.h"
#include "serverNodePath.h"
#include "serverState.h"
#include "serverArmament.h"
//------------------------------------------------------------------------------
// SERVER TASK MOVE MUNITION CONSTRUCTOR
//------------------------------------------------------------------------------
ServerTaskMoveMunition::ServerTaskMoveMunition(
        ServerGame& aGame, ServerNodePath& nodePath, size_t idMunition):
        ServerTask::ServerTask(aGame), idMunition(idMunition) {
    hasExecuted = false;
    this->nodePath = &nodePath;
    this->waitingTime = this->nodePath->getCumulativeWaitingTime();
}
//------------------------------------------------------------------------------
// SERVER TASK MOVE MUNITION DESTRUCTOR
//------------------------------------------------------------------------------
ServerTaskMoveMunition::~ServerTaskMoveMunition() {
    if (!hasExecuted) {
        const ServerState* state = nodePath->getState();
        delete state;
    }
    delete nodePath;
}
//------------------------------------------------------------------------------
// IS RELOCABLE
//------------------------------------------------------------------------------
bool ServerTaskMoveMunition::isRelocable() const {
    return false;
}
//------------------------------------------------------------------------------
// EXECUTE
//------------------------------------------------------------------------------
void ServerTaskMoveMunition::execute() {
    hasExecuted = true;
    aGame.getMunition(idMunition)->changePosition(nodePath->getNode());
    // printf("Munition id: %zu - waitingTime: %f - ", idMunition, waitingTime);
    // nodePath->getNode().showNode();
    aGame.getMunition(idMunition)->changeState(*nodePath->getState());
}
//------------------------------------------------------------------------------
