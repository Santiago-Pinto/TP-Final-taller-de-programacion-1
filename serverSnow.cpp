// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#include "serverSnow.h"
//------------------------------------------------------------------------------
// SNOW CONSTRUCTOR
//------------------------------------------------------------------------------
ServerSnow::ServerSnow(uint32_t x, uint32_t y):
        ServerEarthPrairieSnow::ServerEarthPrairieSnow(x, y) {}
//------------------------------------------------------------------------------
// SNOW DESTRUCTOR
//------------------------------------------------------------------------------
ServerSnow::~ServerSnow() {}
//------------------------------------------------------------------------------
// IS LAVA
//------------------------------------------------------------------------------
bool ServerSnow::isLava() const {
    return false;
}
//------------------------------------------------------------------------------
// IS DUST
//------------------------------------------------------------------------------
bool ServerSnow::isDust() const {
    return false;
}
//------------------------------------------------------------------------------
// IS GRASS
//------------------------------------------------------------------------------
bool ServerSnow::isGrass() const {
    return false;
}
//------------------------------------------------------------------------------
// IS SNOW
//------------------------------------------------------------------------------
bool ServerSnow::isSnow() const {
    return true;
}
//------------------------------------------------------------------------------
// IS WATER
//------------------------------------------------------------------------------
bool ServerSnow::isWater() const {
    return false;
}
//------------------------------------------------------------------------------
// IS SWAMP
//------------------------------------------------------------------------------
bool ServerSnow::isSwamp() const {
    return false;
}
//------------------------------------------------------------------------------
// IS ROAD
//------------------------------------------------------------------------------
bool ServerSnow::isRoad() const {
    return false;
}
//------------------------------------------------------------------------------
// IS ASPHALT ROAD
//------------------------------------------------------------------------------
bool ServerSnow::isAsphaltRoad() const {
    return false;
}
//------------------------------------------------------------------------------
