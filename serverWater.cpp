// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#include "serverWater.h"
//------------------------------------------------------------------------------
// WATER CONSTRUCTOR
//------------------------------------------------------------------------------
ServerWater::ServerWater(uint32_t x, uint32_t y):
        ServerWaterSwamp::ServerWaterSwamp(x, y) {}
//------------------------------------------------------------------------------
// WATER DESTRUCTOR
//------------------------------------------------------------------------------
ServerWater::~ServerWater() {}
//------------------------------------------------------------------------------
// IS LAVA
//------------------------------------------------------------------------------
bool ServerWater::isLava() const {
    return false;
}
//------------------------------------------------------------------------------
// IS DUST
//------------------------------------------------------------------------------
bool ServerWater::isDust() const {
    return false;
}
//------------------------------------------------------------------------------
// IS GRASS
//------------------------------------------------------------------------------
bool ServerWater::isGrass() const {
    return false;
}
//------------------------------------------------------------------------------
// IS SNOW
//------------------------------------------------------------------------------
bool ServerWater::isSnow() const {
    return false;
}
//------------------------------------------------------------------------------
// IS WATER
//------------------------------------------------------------------------------
bool ServerWater::isWater() const {
    return true;
}
//------------------------------------------------------------------------------
// IS SWAMP
//------------------------------------------------------------------------------
bool ServerWater::isSwamp() const {
    return false;
}
//------------------------------------------------------------------------------
// IS ROAD
//------------------------------------------------------------------------------
bool ServerWater::isRoad() const {
    return false;
}
//------------------------------------------------------------------------------
// IS ASPHALT ROAD
//------------------------------------------------------------------------------
bool ServerWater::isAsphaltRoad() const {
    return false;
}
//------------------------------------------------------------------------------