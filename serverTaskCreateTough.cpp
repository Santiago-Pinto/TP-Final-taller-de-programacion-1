// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#include "serverTaskCreateTough.h"
#include "serverGame.h"
#include "serverBuildings.h"
#include "serverPlayer.h"
#include "serverNode.h"
//------------------------------------------------------------------------------
// SERVER TASK CREATE TOUGH CONSTRUCTOR
//------------------------------------------------------------------------------
ServerTaskCreateTough::ServerTaskCreateTough(ServerGame& aGame, size_t idBuilding):
        ServerTask::ServerTask(aGame), idBuilding(idBuilding) {
    ServerBuildings* building = aGame.gameMap.getBuilding(idBuilding);
    size_t takenTerritories = building->getOwner()->getTakenTerritories();
    waitingTime = building->ToughManufacturingTime(takenTerritories);
}
//------------------------------------------------------------------------------
// SERVER TASK CREATE TOUGH DESTRUCTOR
//------------------------------------------------------------------------------
ServerTaskCreateTough::~ServerTaskCreateTough() {}
//------------------------------------------------------------------------------
// IS RELOCABLE
//------------------------------------------------------------------------------
bool ServerTaskCreateTough::isRelocable() const {
    return false;
}
//------------------------------------------------------------------------------
// EXECUTE
//------------------------------------------------------------------------------
void ServerTaskCreateTough::execute() {
    size_t id = ++aGame.unitsQuant;
    ServerBuildings* building = aGame.gameMap.getBuilding(idBuilding);
    uint32_t x = building->getCreationPosition()->x;
    uint32_t y = building->getCreationPosition()->y;
    ServerPlayer* owner = (ServerPlayer *)building->getOwner();
    owner->createRobotTough(x, y, id);
    ServerUnit* newUnit =  owner->getUnit(id);
    aGame.addNewUnit(id, newUnit);
}
//------------------------------------------------------------------------------
