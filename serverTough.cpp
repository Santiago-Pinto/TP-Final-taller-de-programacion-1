// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#include "serverTough.h"
#include "serverSettings.h"
//------------------------------------------------------------------------------
extern Settings settings;
//------------------------------------------------------------------------------
// TOUGH CONSTRUCTOR
//------------------------------------------------------------------------------
ServerTough::ServerTough(const ServerNode& initialPosition, size_t id):
        ServerRobot::ServerRobot(initialPosition, id) {
    shootingFrequency = settings.robotTough["shootingFrequency"];
    reach = settings.robotTough["reach"];
    manufacturing = settings.robotTough["manufacturing"];
    structurePoints = settings.robotTough["structurePoints"];
    minimumTechnologyLevel = settings.robotTough["minimumTechnologyLevel"];
    munitionName = settings.robotToughArmament["armament"];
}
//------------------------------------------------------------------------------
// TOUGH DESTRUCTOR
//------------------------------------------------------------------------------
ServerTough::~ServerTough() {}
//------------------------------------------------------------------------------
// IS GRUNT
//------------------------------------------------------------------------------
bool ServerTough::isGrunt() const {
    return false;
}
//------------------------------------------------------------------------------
// IS TOUGH
//------------------------------------------------------------------------------
bool ServerTough::isTough() const {
    return true;
}
//------------------------------------------------------------------------------
// IS SNIPER
//------------------------------------------------------------------------------
bool ServerTough::isSniper() const {
    return false;
}
//------------------------------------------------------------------------------
// IS PSYCHO
//------------------------------------------------------------------------------
bool ServerTough::isPsycho() const {
    return false;
}
//------------------------------------------------------------------------------
// IS PYRO
//------------------------------------------------------------------------------
bool ServerTough::isPyro() const {
    return false;
}
//------------------------------------------------------------------------------
// IS LASER
//------------------------------------------------------------------------------
bool ServerTough::isLaser() const {
    return false;
}
//------------------------------------------------------------------------------
// IS JEEP
//------------------------------------------------------------------------------
bool ServerTough::isJeep() const {
    return false;
}
//------------------------------------------------------------------------------
// IS MML
//------------------------------------------------------------------------------
bool ServerTough::isMML() const {
    return false;
}
//------------------------------------------------------------------------------
// IS LIGHT TANK
//------------------------------------------------------------------------------
bool ServerTough::isLightTank() const {
    return false;
}
//------------------------------------------------------------------------------
// IS MEDIUM TANK
//------------------------------------------------------------------------------
bool ServerTough::isMediumTank() const {
    return false;
}
//------------------------------------------------------------------------------
// IS HEAVY TANK
//------------------------------------------------------------------------------
bool ServerTough::isHeavyTank() const {
    return false;
}
//------------------------------------------------------------------------------
