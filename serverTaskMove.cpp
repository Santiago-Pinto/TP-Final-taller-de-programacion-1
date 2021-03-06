// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#include "serverTaskMove.h"
#include "serverGame.h"
#include "serverPlayer.h"
#include "serverNode.h"
#include "serverNodePath.h"
#include "serverState.h"
//------------------------------------------------------------------------------
// SERVER TASK MOVE UNIT CONSTRUCTOR
//------------------------------------------------------------------------------
ServerTaskMove::ServerTaskMove(
        ServerGame& aGame, ServerNodePath& nodePath, size_t idUnit):
        ServerTask::ServerTask(aGame), idUnit(idUnit) {
    hasExecuted = false;
    this->nodePath = &nodePath;
    waitingTime = this->nodePath->getCumulativeWaitingTime();
}
//------------------------------------------------------------------------------
// SERVER TASK MOVE UNIT DESTRUCTOR
//------------------------------------------------------------------------------
ServerTaskMove::~ServerTaskMove() {
    if (!hasExecuted) {
        const ServerState* state = nodePath->getState();
        delete state;
    }
    delete nodePath;
}
//------------------------------------------------------------------------------
// IS RELOCABLE
//------------------------------------------------------------------------------
bool ServerTaskMove::isRelocable() const {
    return false;
}
//------------------------------------------------------------------------------
// EXECUTE
//------------------------------------------------------------------------------
void ServerTaskMove::execute() {
    hasExecuted = true;
    aGame.getUnit(idUnit)->changePosition(nodePath->getNode());
    // printf("waitingTime: %f - ", waitingTime);
    // nodePath->getNode().showNode();
    aGame.getUnit(idUnit)->changeState(*nodePath->getState());
}
//------------------------------------------------------------------------------
