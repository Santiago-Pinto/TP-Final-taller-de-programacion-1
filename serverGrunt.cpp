// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#include "serverGrunt.h"
#include "serverSettings.h"
//------------------------------------------------------------------------------
extern Settings settings;
//------------------------------------------------------------------------------
// GRUNT CONSTRUCTOR
//------------------------------------------------------------------------------
ServerGrunt::ServerGrunt(const ServerNode& initialPosition, size_t id):
        ServerRobot::ServerRobot(initialPosition, id) {
    shootingFrequency = settings.robotGrunt["shootingFrequency"];
    reach = settings.robotGrunt["reach"];
    manufacturing = settings.robotGrunt["manufacturing"];
    structurePoints = settings.robotGrunt["structurePoints"];
    minimumTechnologyLevel = settings.robotGrunt["minimumTechnologyLevel"];
    munitionName = settings.robotGruntArmament["armament"];
}
//------------------------------------------------------------------------------
// GRUNT DESTRUCTOR
//------------------------------------------------------------------------------
ServerGrunt::~ServerGrunt() {}
//------------------------------------------------------------------------------
// IS GRUNT
//------------------------------------------------------------------------------
bool ServerGrunt::isGrunt() const {
    return true;
}
//------------------------------------------------------------------------------
// IS TOUGH
//------------------------------------------------------------------------------
bool ServerGrunt::isTough() const {
    return false;
}
//------------------------------------------------------------------------------
// IS SNIPER
//------------------------------------------------------------------------------
bool ServerGrunt::isSniper() const {
    return false;
}
//------------------------------------------------------------------------------
// IS PSYCHO
//------------------------------------------------------------------------------
bool ServerGrunt::isPsycho() const {
    return false;
}
//------------------------------------------------------------------------------
// IS PYRO
//------------------------------------------------------------------------------
bool ServerGrunt::isPyro() const {
    return false;
}
//------------------------------------------------------------------------------
// IS LASER
//------------------------------------------------------------------------------
bool ServerGrunt::isLaser() const {
    return false;
}
//------------------------------------------------------------------------------
// IS JEEP
//------------------------------------------------------------------------------
bool ServerGrunt::isJeep() const {
    return false;
}
//------------------------------------------------------------------------------
// IS MML
//------------------------------------------------------------------------------
bool ServerGrunt::isMML() const {
    return false;
}
//------------------------------------------------------------------------------
// IS LIGHT TANK
//------------------------------------------------------------------------------
bool ServerGrunt::isLightTank() const {
    return false;
}
//------------------------------------------------------------------------------
// IS MEDIUM TANK
//------------------------------------------------------------------------------
bool ServerGrunt::isMediumTank() const {
    return false;
}
//------------------------------------------------------------------------------
// IS HEAVY TANK
//------------------------------------------------------------------------------
bool ServerGrunt::isHeavyTank() const {
    return false;
}
//------------------------------------------------------------------------------