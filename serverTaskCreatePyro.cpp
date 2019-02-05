// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#include "serverTaskCreatePyro.h"
#include "serverGame.h"
#include "serverBuildings.h"
#include "serverPlayer.h"
#include "serverNode.h"
//------------------------------------------------------------------------------
// SERVER TASK CREATE PYRO CONSTRUCTOR
//------------------------------------------------------------------------------
ServerTaskCreatePyro::ServerTaskCreatePyro(ServerGame& aGame, size_t idBuilding):
        ServerTask::ServerTask(aGame), idBuilding(idBuilding) {
    ServerBuildings* building = aGame.gameMap.getBuilding(idBuilding);
    size_t takenTerritories = building->getOwner()->getTakenTerritories();
    waitingTime = building->PyroManufacturingTime(takenTerritories);
}
//------------------------------------------------------------------------------
// SERVER TASK CREATE PYRO DESTRUCTOR
//------------------------------------------------------------------------------
ServerTaskCreatePyro::~ServerTaskCreatePyro() {}
//------------------------------------------------------------------------------
// IS RELOCABLE
//------------------------------------------------------------------------------
bool ServerTaskCreatePyro::isRelocable() const {
    return false;
}
//------------------------------------------------------------------------------
// EXECUTE
//------------------------------------------------------------------------------
void ServerTaskCreatePyro::execute() {
    size_t id = ++aGame.unitsQuant;
    ServerBuildings* building = aGame.gameMap.getBuilding(idBuilding);
    uint32_t x = building->getCreationPosition()->x;
    uint32_t y = building->getCreationPosition()->y;
    ServerPlayer* owner = (ServerPlayer *)building->getOwner();
    owner->createRobotPyro(x, y, id);
    ServerUnit* newUnit =  owner->getUnit(id);
    aGame.addNewUnit(id, newUnit);
}
//------------------------------------------------------------------------------
