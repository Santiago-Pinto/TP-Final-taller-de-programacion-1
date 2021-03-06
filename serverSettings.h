// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#ifndef _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERSETTINGS_H_
#define _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERSETTINGS_H_
//------------------------------------------------------------------------------
#include <string>
#include "commonDicc.h"
//------------------------------------------------------------------------------
typedef commonDicc<std::string, size_t> DiccArmament;
typedef commonDicc<std::string, std::string> ArmamentOfManufactured;
typedef commonDicc<std::string, float> DiccSettings;
typedef commonDicc<std::string, uint32_t> DiccMap;
typedef commonDicc<std::string, size_t> Objects;
//------------------------------------------------------------------------------
class Settings {
 public :
    DiccArmament bullets;
    DiccArmament highCaliberProjectiles;
    DiccArmament missiles;
    DiccArmament flamethrower;
    DiccArmament laser;

    DiccSettings robotGrunt;
    DiccSettings robotTough;
    DiccSettings robotSniper;
    DiccSettings robotPsycho;
    DiccSettings robotPyro;
    DiccSettings robotLaser;

    ArmamentOfManufactured robotGruntArmament;
    ArmamentOfManufactured robotToughArmament;
    ArmamentOfManufactured robotSniperArmament;
    ArmamentOfManufactured robotPsychoArmament;
    ArmamentOfManufactured robotPyroArmament;
    ArmamentOfManufactured robotLaserArmament;

    DiccSettings vehicleJeep;
    DiccSettings vehicleLightTank;
    DiccSettings vehicleMML;
    DiccSettings vehicleMediumTank;
    DiccSettings vehicleHeavyTank;

    ArmamentOfManufactured vehicleJeepArmament;
    ArmamentOfManufactured vehicleLightTankArmament;
    ArmamentOfManufactured vehicleMMLArmament;
    ArmamentOfManufactured vehicleMediumTankArmament;
    ArmamentOfManufactured vehicleHeavyTankArmament;

    DiccSettings EarthPrairieSnow;
    DiccSettings WaterSwamp;
    DiccSettings RoadAsphaltRoad;
    DiccSettings Lava;

    Objects ConcreteAndWoodenBridges;
    Objects StoneIceBlocks;
    Objects Buildings;

    DiccMap aMap;
 public :
    //--------------------------------------------------------------------------
    Settings();
    //--------------------------------------------------------------------------
    ~Settings();
    //--------------------------------------------------------------------------
};
//------------------------------------------------------------------------------
#endif  // _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_SERVERSETTINGS_H_
