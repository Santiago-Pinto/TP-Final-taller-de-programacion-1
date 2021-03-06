#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include "client_Map.h"
#include "client_Robot.h"
#include "client_Grunt.h"
#include "client_Laser.h"
#include "client_GrassTile.h"
#include "client_SwampTile.h"
#include "client_WoodBridge.h"
#include "client_WalkAction.h"
#include "client_ShootAction.h"
#include "client_Flag.h"
#include "client_Fort.h"
#include "client_LightTank.h"
#include "client_StandStillAction.h"
#include "client_DieAction.h"
#include "client_RFactory.h"
#include "client_VFactory.h"
#include "client_ConcreteBridge.h"
#include "client_Rock.h"
#include "client_IceBlock.h"
#include "client_SnowTile.h"
#include "client_HighWayTile.h"
#include "client_LavaTile.h"
#include "client_DustTile.h"
#include "client_RoadAsphaltTile.h"
#include "client_WaterTile.h"

#include "serverFort.h"
#include "serverArmament.h"
#include "serverUnit.h"
#include "serverNode.h"
#include "serverStateMoving.h"
#include "serverTerritories.h"
#include "serverObject.h"

#include "clientProxyGame.h"
#include "clientProxyTerritories.h"
#include "clientProxyNode.h"
#include "clientProxyObject.h"
#include "clientProxyMunition.h"
#include "clientProxyUnit.h"
#include "client_Psycho.h"
#include "client_Tough.h"
#include "client_Pyro.h"
#include "client_Sniper.h"
#include "client_Jeep.h"
#include "client_MediumTank.h"
#include "client_HeavyTank.h"
#include "client_MML.h"
#include "client_OutcomeWindow.h"
#include "commonLock.h"
//------------------------------------------------------------------------------
using std::map;
using std::vector;
using std::pair;
//------------------------------------------------------------------------------
typedef std::vector<std::vector<ServerNode*>> mapMatrix;
//------------------------------------------------------------------------------
// MAP CONSTRUCTOR
//------------------------------------------------------------------------------
Map::Map(ClientProxyGame& aGame): unit_count(0), aGame(aGame) {
    finish = false;
}
//------------------------------------------------------------------------------
// DRAW MAP
//------------------------------------------------------------------------------
void Map::drawMap() {
    for (ClientProxyTerritories* territory : aGame.getTerritories().getList()) {
        std::vector<Tile*> tiles;
        std::vector<ClientProxyNode*>& nodes = territory->getNodes();
        for (const ClientProxyNode* aNode : nodes) {
            addNode(*aNode, tiles);
        }
        territories.push_back(new Territory(tiles));
    }
}
//------------------------------------------------------------------------------
// SHOW OUTCOME
//------------------------------------------------------------------------------
void Map::showOutcome(bool victory, SDL_Surface* screen) {
    if (victory) {
        ClientOutcomeWindow outcome("victory");
        outcome.draw(screen);
    } else {
        ClientOutcomeWindow outcome("defeat");
        outcome.draw(screen);
    }
    finish = true;
}
//------------------------------------------------------------------------------
// MAP DESTRUCTOR
//------------------------------------------------------------------------------
Map::~Map() {
    //--------------------------------------------------------------------------
    map<unsigned int, Unit*>::iterator unit_it = units.begin();
    while (unit_it != units.end()) {
        delete unit_it->second;
        ++unit_it;
    }
    //--------------------------------------------------------------------------
    vector<Territory*>::iterator territory_it = territories.begin();
    while (territory_it != territories.end()) {
        delete (*territory_it);
        ++territory_it;
    }
    //--------------------------------------------------------------------------
    map<unsigned int, ClientAmmo*>::iterator bullets_it = bullet_map.begin();
    while (bullets_it != bullet_map.end()) {
        delete bullets_it->second;
        ++bullets_it;
    }
    //--------------------------------------------------------------------------
    map<unsigned int, TerrainObject*>::iterator obj_it = objects.begin();
    while (obj_it != objects.end()) {
        delete obj_it->second;
        ++obj_it;
    }
    //--------------------------------------------------------------------------
    map<unsigned int, ClientBuilding*>::iterator build_it = buildings.begin();
    while (build_it != buildings.end()) {
        delete build_it->second;
        ++build_it;
    }
    //--------------------------------------------------------------------------
    map<unsigned int,ClientExplosion*>::iterator explosion_it;
    explosion_it = explosion_map.begin();
    while (explosion_it != explosion_map.end()) {
        delete explosion_it->second;
        ++explosion_it;
    }
    //--------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
// ADD NODE
//------------------------------------------------------------------------------
void Map::addNode(const ClientProxyNode& aNode, std::vector<Tile *>& tiles) {
    uint32_t pixelX = tileToCornerPixel(aNode.getX());
    uint32_t pixelY = tileToCornerPixel(aNode.getY());
    if (aNode.isWater()) {
        tiles.push_back(new WaterTile(pixelX, pixelY));
    } else if (aNode.isSwamp()) {
        tiles.push_back(new SwampTile(pixelX, pixelY));
    } else if (aNode.isAsphaltRoad()) {
        tiles.push_back(new RoadAsphaltTile(pixelX, pixelY));
    } else if (aNode.isRoad()) {
        tiles.push_back(new HighWayTile(pixelX, pixelY));
    } else if (aNode.isSnow()) {
        tiles.push_back(new SnowTile(pixelX, pixelY));
    } else if (aNode.isGrass()) {
        tiles.push_back(new GrassTile(pixelX, pixelY));
    } else if (aNode.isDust()) {
        tiles.push_back(new DustTile(pixelX, pixelY));
    } else if (aNode.isLava()) {
        tiles.push_back(new LavaTile(pixelX, pixelY));
    }
    addObject(aNode);
}
//------------------------------------------------------------------------------
// ADD OBJECT
//------------------------------------------------------------------------------
void Map::addObject(const ClientProxyNode& aNode) {
    if (!aNode.hasAnObject()) return;
    const ClientProxyObject* object = aNode.getGroundObject();
    uint32_t pixelX = tileToCornerPixel(object->getPrincipalPosition().getX());
    uint32_t pixelY = tileToCornerPixel(object->getPrincipalPosition().getY());
    unsigned int id = (unsigned int)object->getId();
    unsigned int ownerId = (unsigned int)object->getOwnerId();
    if (object->isWoodenBridge()) {
        this->add_terrain_object(new WoodBridge(id, pixelX, pixelY));
    } else if (object->isConcreteBridge()) {
        this->add_terrain_object(new ConcreteBridge(id, pixelX, pixelY));
    } else if (object->isBuilding()) {
        unsigned int tecnologyLevel;
        tecnologyLevel = (unsigned int)object->getTecnologyLevel();
        if (object->isFort()) {
            create_fort(id, ownerId, pixelX, pixelY, tecnologyLevel);
        } else if (object->isRobotFactorie()) {
            create_robot_factory(id, ownerId, pixelX, pixelY, tecnologyLevel);
        } else if (object->isVehicleFactorie()) {
            create_vehicle_factory(id, ownerId, pixelX, pixelY, tecnologyLevel);
        }
    } else if (object->isFlag()) {
        Flag* flag = new Flag(id, pixelX, pixelY);
        flag->change_owner(ownerId);
        this->add_terrain_object(flag);
    } else if (object->isStone()) {
        this->add_terrain_object(new ClientRock(id, pixelX, pixelY));
    } else if (object->isIceBlock()) {
        this->add_terrain_object(new ClientIceBlock(id, pixelX, pixelY));
    }
}
//------------------------------------------------------------------------------
// DRAW
//------------------------------------------------------------------------------
void Map::draw(SDL_Surface* screen, ClientCamera& camera) {
    if (finish) return;
    for (Territory* & territory : territories) {
        territory->draw(screen, camera);
    }
    //--------------------------------------------------------------------------
    map<unsigned int, ClientBuilding*>::iterator build_it = buildings.begin();
    while (build_it != buildings.end()) {
        build_it->second->draw(screen, camera);
        ++build_it;
    }
    //--------------------------------------------------------------------------
    std::map<unsigned int, TerrainObject*>::iterator obj_it = objects.begin();
    while (obj_it != objects.end()) {
        obj_it->second->draw(screen, camera);
        ++obj_it;
    }
    //--------------------------------------------------------------------------
    vector<Unit*> dead_units;
    std::map<unsigned int, Unit*>::iterator unit_it = units.begin();
    while (unit_it != units.end()) {
        if (unit_it->second->is_dead()) {
            dead_units.push_back(unit_it->second);
        } else {
            unit_it->second->draw(screen, camera);
        }
        ++unit_it;
    }
    //--------------------------------------------------------------------------
    map<unsigned int, ClientAmmo*>::iterator bullets_it = bullet_map.begin();
    while (bullets_it != bullet_map.end()) {
        if (!bullets_it->second->collisioned()) {
            bullets_it->second->draw(screen, camera);
        }
        ++bullets_it;
    }
    //--------------------------------------------------------------------------
    vector<ClientExplosion*> finished_explosions;
    map<unsigned int, ClientExplosion*>::iterator explosion_it;
    explosion_it = explosion_map.begin();
    while (explosion_it != explosion_map.end()) {
        if (!explosion_it->second->finished()) {
            explosion_it->second->draw(screen,camera);
        } else {
            finished_explosions.push_back(explosion_it->second);
        }
        ++explosion_it;
    }
    //--------------------------------------------------------------------------
    check_bullets_collisions();
    handle_explosions(finished_explosions);
    handle_dead_units(dead_units);
}
//------------------------------------------------------------------------------
// ADD TERRAIN OBJECT
//------------------------------------------------------------------------------
void Map::add_terrain_object(TerrainObject* object) {
    unsigned int id = object->get_id();
    objects.insert(pair<unsigned int, TerrainObject*>(id, object));
    unit_count++;
}
//------------------------------------------------------------------------------
// SEARCH UNIT BY POSITION
//------------------------------------------------------------------------------
int Map::search_unit_by_position(int x, int y, unsigned int player_id) {
    std::map<unsigned int,Unit*>::iterator unit_it = units.begin();
    while (unit_it != units.end()){
        Unit* unit = unit_it->second;
        if (unit->get_owner_id() == player_id && unit->is_selected(x,y)){
            return unit_it->second->get_id();
        }
        ++unit_it;
    }
    return -1; // no se encontro coincidencia
}
//------------------------------------------------------------------------------
// SEARCH UNIT BY POSITION
//------------------------------------------------------------------------------
int Map::search_building_by_position(int x, int y, unsigned int player_id) {
    map<unsigned int,ClientBuilding*>::iterator build_it = buildings.begin();
    while (build_it != buildings.end()){
        ClientBuilding* building = build_it->second;
        if (building->get_owner_id() == player_id &&
            building->is_selected(x,y)){
            return build_it->second->get_id();
        }
        ++build_it;
    }
    return -1; // no se encontro coincidencia
}
//------------------------------------------------------------------------------
// SEARCH OBJECT BY POSITION
//------------------------------------------------------------------------------
GameObject* Map::search_object_by_position(int x, int y) {
    //--------------------------------------------------------------------------
    std::map<unsigned int,Unit*>::iterator unit_it = units.begin();
    while (unit_it != units.end()) {
        if (unit_it->second->is_selected(x,y)) {
            return unit_it->second;
        }
        ++unit_it;
    }
    //--------------------------------------------------------------------------
    map<unsigned int,ClientBuilding*>::iterator build_it = buildings.begin();
    while (build_it != buildings.end()) {
        if (build_it->second->is_selected(x, y)) {
            return build_it->second;
        }
        ++build_it;
    }
    //--------------------------------------------------------------------------
    map<unsigned int,TerrainObject*>::iterator object_it = objects.begin();
    while (object_it != objects.end()) {
        TerrainObject* object = object_it->second;
        if (object->is_selected(x, y) && object->can_be_attacked()) {
            return object_it->second;
        }
        ++object_it;
    }
    //--------------------------------------------------------------------------
    return nullptr;
}
//------------------------------------------------------------------------------
// UNIT MOVE
//------------------------------------------------------------------------------
void Map::unitMove(
        unsigned int id, unsigned int dest_x, unsigned int dest_y,
        double speed) {
    Unit* unit_ptr = units.at(id);
    unit_ptr->new_command(new WalkAction(unit_ptr, dest_x, dest_y, speed));
}
//------------------------------------------------------------------------------
// BULLET MOVE
//------------------------------------------------------------------------------
void Map::bullet_move(
        unsigned int id, unsigned int dest_x, unsigned int dest_y,
                 double speed) {
    ClientAmmo* bullet = bullet_map.at(id);
    bullet->move(dest_x, dest_y, speed);
}
//------------------------------------------------------------------------------
// UNIT SHOOT
//------------------------------------------------------------------------------
void Map::unit_shoot(
        unsigned int shooter_id, GameObject* target, unsigned int bullet_id) {
    if (!unitExist(shooter_id)) return;
    Unit* shooter = units.at(shooter_id);
    shooter->new_command(new ShootAction(shooter, target));
    ClientAmmo* ammo = shooter->get_bullet(bullet_id, shooter, target);
    bullet_map.insert(pair<unsigned int, ClientAmmo*> (bullet_id, ammo));
}
//------------------------------------------------------------------------------
// UNIT STAND STILL
//------------------------------------------------------------------------------
void Map::unit_stand_still(unsigned int id) {
    Unit* unit_ptr = units.at(id);
    unit_ptr->new_command(new StandStillAction(unit_ptr));
}
//------------------------------------------------------------------------------
// UNIT DIED
//------------------------------------------------------------------------------
void Map::unit_died(unsigned int id) {
    Unit* unit_ptr = units.at(id);
    unit_ptr->new_command(new DieAction(unit_ptr));
}
//------------------------------------------------------------------------------
// CREATE GRUNT
//------------------------------------------------------------------------------
void Map::create_grunt(unsigned int id, unsigned int owner_id,
                       unsigned int x, unsigned int y){
    units.insert(pair<unsigned int, Unit*>
                         (id, new ClientRobotGrunt(id,owner_id,x,y)));
    unit_count++;
}

//------------------------------------------------------------------------------
// CREATE LASER
//------------------------------------------------------------------------------
void Map::create_laser(unsigned int id, unsigned int owner_id,
                       unsigned int x, unsigned int y){
    units.insert(pair<unsigned int, Unit*>
                         (id, new ClientRobotLaser(id,owner_id,x,y)));
    unit_count++;
}
//------------------------------------------------------------------------------
// CREATE PSYCHO
//------------------------------------------------------------------------------
void Map::create_psycho(unsigned int id, unsigned int owner_id,
                        unsigned int x, unsigned int y){
    units.insert(pair<unsigned int, Unit*>
                         (id, new ClientRobotPsycho(id,owner_id,x,y)));
    unit_count++;
}
//------------------------------------------------------------------------------
// CREATE TOUGH
//------------------------------------------------------------------------------
void Map::create_tough(unsigned int id, unsigned int owner_id,
                       unsigned int x, unsigned int y){
    units.insert(pair<unsigned int, Unit*>
                         (id, new ClientRobotTough(id,owner_id,x,y)));
    unit_count++;
}
//------------------------------------------------------------------------------
// CREATE PYRO
//------------------------------------------------------------------------------
void Map::create_pyro(unsigned int id, unsigned int owner_id,
                      unsigned int x, unsigned int y){
    units.insert(pair<unsigned int, Unit*>
                         (id, new ClientRobotPyro(id,owner_id,x,y)));
    unit_count++;
}
//------------------------------------------------------------------------------
// CREATE SNIPER
//------------------------------------------------------------------------------
void Map::create_sniper(unsigned int id, unsigned int owner_id,
                        unsigned int x, unsigned int y){
    units.insert(pair<unsigned int, Unit*>
                         (id, new ClientRobotSniper(id,owner_id,x,y)));
    unit_count++;
}
//------------------------------------------------------------------------------
// CREATE LIGHT TANK
//------------------------------------------------------------------------------
void Map::create_light_tank(unsigned int id, unsigned int owner_id,
                            unsigned int x, unsigned int y){
    units.insert(pair<unsigned int, Unit*>
                         (id, new ClientLightTank(id,owner_id,x,y)));
    unit_count++;
}
//------------------------------------------------------------------------------
// CREATE JEEP
//------------------------------------------------------------------------------
void Map::create_jeep(unsigned int id, unsigned int owner_id,
                      unsigned int x, unsigned int y){
    units.insert(pair<unsigned int, Unit*>
                         (id, new ClientJeep(id,owner_id,x,y)));
    unit_count++;
}
//------------------------------------------------------------------------------
// CREATE MEDIUM TANK
//------------------------------------------------------------------------------
void Map::create_medium_tank(unsigned int id, unsigned int owner_id,
                             unsigned int x, unsigned int y){
    units.insert(pair<unsigned int, Unit*>
                         (id, new ClientMediumTank(id,owner_id,x,y)));
    unit_count++;
}
//------------------------------------------------------------------------------
// CREATE HEAVY TANK
//------------------------------------------------------------------------------
void Map::create_heavy_tank(unsigned int id, unsigned int owner_id,
                            unsigned int x, unsigned int y){
    units.insert(pair<unsigned int, Unit*>
                         (id, new ClientHeavyTank(id,owner_id,x,y)));
    unit_count++;
}
//------------------------------------------------------------------------------
// CREATE MML
//------------------------------------------------------------------------------
void Map::create_MML(unsigned int id, unsigned int owner_id,
                     unsigned int x, unsigned int y){
    units.insert(pair<unsigned int, Unit*>
                         (id, new ClientMML(id,owner_id,x,y)));
    unit_count++;
}
//------------------------------------------------------------------------------
//******************************************************************************
// CREATE BUILDINGS
//******************************************************************************
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// CREATE FORT
//------------------------------------------------------------------------------
void Map::create_fort(unsigned int id, unsigned int owner_id,
                      unsigned int x,unsigned int y, unsigned int tech_level) {
    if (buildingExist(id)) return;
    buildings.insert(pair<unsigned int, ClientBuilding*>
                  (id, new ClientFort(id, owner_id, x, y, tech_level)));
}
//------------------------------------------------------------------------------
// CREATE ROBOT FACTORIE
//------------------------------------------------------------------------------
void Map::create_robot_factory(
        unsigned int id, unsigned int owner_id, unsigned int x, unsigned int y,
        unsigned int tech_level) {
    if (buildingExist(id)) return;
    buildings.insert(pair<unsigned int, ClientBuilding*>
                      (id, new ClientRFactory(id, owner_id, x, y, tech_level)));
}
//------------------------------------------------------------------------------
// CREATE VEHICLE FACTORIE
//------------------------------------------------------------------------------
void Map::create_vehicle_factory(
        unsigned int id, unsigned int owner_id, unsigned int x, unsigned int y,
        unsigned int tech_level) {
    if (buildingExist(id)) return;
    buildings.insert(pair<unsigned int, ClientBuilding*>
                    (id, new ClientVFactory(id, owner_id, x, y, tech_level)));
}
//------------------------------------------------------------------------------
//******************************************************************************
// TERRITORY CAPTURE
//******************************************************************************
//------------------------------------------------------------------------------
// CHANGE BUILDING OWNER
//------------------------------------------------------------------------------
void Map::change_building_owner(unsigned int id, unsigned int owner_id){
    ClientBuilding* building = buildings.at(id);
    building->change_owner(owner_id);
}
//------------------------------------------------------------------------------
// CHANGE FLAG OWNER
//------------------------------------------------------------------------------
void Map::change_flag_owner(unsigned int id, unsigned int owner_id){
    Flag* flag = (Flag*)objects.at(id);
    flag->change_owner(owner_id);
}
//------------------------------------------------------------------------------
// DESTROY BUILDING
//------------------------------------------------------------------------------
void Map::destroy_building(unsigned int id){
    ClientBuilding* building = buildings.at(id);
    building->destroy();
}
//------------------------------------------------------------------------------
// DESTROY BRIDGE
//------------------------------------------------------------------------------
void Map::destroy_bridge(unsigned int id){
    WoodBridge* bridge = (WoodBridge*)objects.at(id);
    bridge->destroy();
}
//------------------------------------------------------------------------------
// DESTROY OBSTACLE
//------------------------------------------------------------------------------
void Map::destroy_obstacle(unsigned int id){
    ClientRock* rock = (ClientRock*)objects.at(id);
    rock->destroy();
}
//------------------------------------------------------------------------------
// EXPLOSION EXIST
//------------------------------------------------------------------------------
bool Map::explosionExist(unsigned int id) {
    try {
        explosion_map.at(id);
        return true;
    } catch (const std::out_of_range& oor) {
        return false;
    }
}
//------------------------------------------------------------------------------
// UNIT EXIST
//------------------------------------------------------------------------------
bool Map::unitExist(unsigned int id) {
    try {
        units.at(id);
        return true;
    } catch (const std::out_of_range& oor) {
        return false;
    }
}
//------------------------------------------------------------------------------
// TERRAIN OBJECT EXIST
//------------------------------------------------------------------------------
bool Map::terrainObjectExist(unsigned int id) const {
    try {
        objects.at(id);
        return true;
    } catch (const std::out_of_range& oor) {
        return false;
    }
}
//------------------------------------------------------------------------------
// MUNITION EXIST
//------------------------------------------------------------------------------
bool Map::bulletExist(unsigned int id) {
    try {
        bullet_map.at(id);
        return true;
    } catch (const std::out_of_range& oor) {
        return false;
    }
}
//------------------------------------------------------------------------------
// BUILDING EXIST
//------------------------------------------------------------------------------
bool Map::buildingExist(unsigned int id) {
    try {
        buildings.at(id);
        return true;
    } catch (const std::out_of_range& oor) {
        return false;
    }
}
//------------------------------------------------------------------------------
// TILE TO CORNER PIXEL
//------------------------------------------------------------------------------
uint32_t Map::tileToCornerPixel(uint32_t number) {
    return 64 * number;
}
//------------------------------------------------------------------------------
// PIXEL TO TILE
//------------------------------------------------------------------------------
uint32_t Map::pixelToTile(uint32_t number) {
    return number / 64;
}
//------------------------------------------------------------------------------
// TILE TO CENTRAL PIXEL
//------------------------------------------------------------------------------
uint32_t Map::tileToCentralPixel(uint32_t number) {
    return 32 * (2 * number + 1);
}
//------------------------------------------------------------------------------
// CREATE BULLET
//------------------------------------------------------------------------------
void Map::createBullet(ClientProxyMunition& aMunition) {
    unsigned int id = (unsigned int)aMunition.getId();
    unsigned int idShooter = (unsigned int)aMunition.getIdShooter();
    unsigned int idTarget = (unsigned int)aMunition.getIdTarget();
    GameObject* target = nullptr;
    if (aMunition.isTargetAnObject()) {
        if (buildingExist(idTarget)) {
            if (!buildingExist(idTarget)) return;
            target = buildings.at(idTarget);
        } else if (terrainObjectExist(idTarget)) {
            if (!terrainObjectExist(idTarget)) return;
            target = objects.at(idTarget);
        }
    } else {
        if (!unitExist(idTarget)) return;
        target = units.at(idTarget);
    }
    unit_shoot(idShooter, target, id);
}
//------------------------------------------------------------------------------
// UPDATE BULLET
//------------------------------------------------------------------------------
void Map::updateBullet(ClientProxyMunition& aMunition) {
    unsigned int id = (unsigned int)aMunition.getId();
    unsigned int x, y;
    if (aMunition.isMoving()) {
        x = tileToCentralPixel(aMunition.movingTo()->getX());
        y = tileToCentralPixel(aMunition.movingTo()->getY());
        bullet_move(id, x, y, aMunition.getSpeed());
    } else if (aMunition.isObsolete()) {
        ClientAmmo* brokenBullet = bullet_map.at(id);
        brokenBullet->target_died(nullptr);
    }

}
//------------------------------------------------------------------------------
// CREATE UNIT
//------------------------------------------------------------------------------
void Map::createUnit(ClientProxyUnit& aUnit) {
    unsigned int id = (unsigned int)aUnit.getId();
    unsigned int x = tileToCentralPixel(aUnit.getPosition()->getX());
    unsigned int y = tileToCentralPixel(aUnit.getPosition()->getY());
    unsigned int ownerId = (unsigned int)aUnit.getOwnerId();
    if (aUnit.isGrunt()) {
        create_grunt(id, ownerId, x, y);
    } else if (aUnit.isLaser()) {
        create_laser(id, ownerId, x, y);
    } else if (aUnit.isPsycho()) {
        create_psycho(id, ownerId, x, y);
    } else if (aUnit.isPyro()) {
        create_pyro(id, ownerId, x, y);
    } else if (aUnit.isSniper()) {
        create_sniper(id, ownerId, x, y);
    } else if (aUnit.isTough()) {
        create_tough(id, ownerId, x, y);
    } else if (aUnit.isMML()) {
        create_MML(id, ownerId, x, y);
    } else if (aUnit.isJeep()) {
        create_jeep(id, ownerId, x, y);
    } else if (aUnit.isLightTank()) {
        create_light_tank(id, ownerId, x, y);
    } else if (aUnit.isMediumTank()) {
        create_medium_tank(id, ownerId, x, y);
    } else if (aUnit.isHeavyTank()) {
        create_heavy_tank(id, ownerId, x, y);
    } else {
        throw Exception("No existe el robot");
    }
}
//------------------------------------------------------------------------------
// UPDATE UNIT
//------------------------------------------------------------------------------
void Map::updateUnit(ClientProxyUnit& aUnit) {
    unsigned int id = (unsigned int)aUnit.getId();
    bool  a = aUnit.isMoving() && aUnit.positionHasChanged();
    bool  b = aUnit.isMoving() && aUnit.lastStateIsStill();
    if (a || b) {
        unsigned int destX = tileToCentralPixel(aUnit.movingTo()->getX());
        unsigned int destY = tileToCentralPixel(aUnit.movingTo()->getY());
        double speed = 1.8 * aUnit.getSpeed(*aUnit.getPosition());
        unitMove((unsigned int)aUnit.getId(), destX, destY, speed);
    } else if (aUnit.isStill()) {
        unit_stand_still(id);
    } else if (aUnit.isDead()) {
        unit_died(id);
    }
}
//------------------------------------------------------------------------------
// UPDATE MAP
//------------------------------------------------------------------------------
void Map::updateMap() {
    //--------------------------------------------------------------------------
    refreshMap();
    //--------------------------------------------------------------------------
    for (ClientProxyMunition* aMunition : aGame.getMunitions().getList()) {
        if (bulletExist((unsigned int)aMunition->getId())) {
            updateBullet(*aMunition);
        } else {
            createBullet(*aMunition);
        }
    }
    //--------------------------------------------------------------------------
    const std::vector<ClientProxyUnit*>& unitsList = aGame.getUnits().getList();
    for (ClientProxyUnit* aUnit : unitsList) {
        if (unitExist((unsigned int)aUnit->getId())) {
            updateUnit(*aUnit);
        } else {
            createUnit(*aUnit);
        }
    }
    //--------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
// UPDATE TERRAIN OBJECT
//------------------------------------------------------------------------------
void Map::updateTerrainObject(const ClientProxyObject& anObject) {
    unsigned int id = (unsigned int)anObject.getId();
    if (anObject.isFlag()) {
        Flag* flag = (Flag*)objects.at(id);
        flag->change_owner((unsigned int)anObject.getOwnerId());
        return;
    }
    if (!anObject.isBroken()) return;
    if (anObject.isWoodenBridge()) {
        WoodBridge* aWoodBridge = (WoodBridge*)objects.at(id);
        aWoodBridge->destroy();
    } else if (anObject.isConcreteBridge()) {
        ConcreteBridge* concreteBridge = (ConcreteBridge*)objects.at(id);
        concreteBridge->destroy();
    } else if (anObject.isStone()) {
        ClientRock* rock = (ClientRock*)objects.at(id);
        rock->destroy();
    } else if (anObject.isIceBlock()) {
        ClientIceBlock* iceBlock = (ClientIceBlock*)objects.at(id);
        iceBlock->destroy();
    }
}
//------------------------------------------------------------------------------
// UPDATE BUILDING
//------------------------------------------------------------------------------
void Map::updateBuilding(const ClientProxyObject& anObject) {
    unsigned int id = (unsigned int)anObject.getId();
    unsigned int ownerId = (unsigned int)anObject.getOwnerId();
    ClientBuilding* building = buildings.at(id);
    if (anObject.isBroken()) {
        building->destroy();
        return;
    }
    building->change_owner(ownerId);
}
//------------------------------------------------------------------------------
// REFRESH MAP
//------------------------------------------------------------------------------
void Map::refreshMap() {
    std::vector<ClientProxyObject*>& objects = aGame.getObjects().getList();
    for (ClientProxyObject* anObject : objects) {
        unsigned int id = (unsigned int)anObject->getId();
        if (anObject->isBuilding()) {
            if (!buildingExist(id)) {
                addObject(anObject->getPrincipalPosition());
            } else {
                updateBuilding(*anObject);
            }
        } else {
            if (!terrainObjectExist(id)) {
                addObject(anObject->getPrincipalPosition());
            } else {
                updateTerrainObject(*anObject);
            }
        }
    }
}
//------------------------------------------------------------------------------
// BUTTON SELECTED
//------------------------------------------------------------------------------
void Map::button_selected(unsigned int mouse_x, unsigned int mouse_y) {
    map<unsigned int, ClientBuilding*>::iterator build_it = buildings.begin();
    while (build_it != buildings.end()) {
        build_it->second->check_button_pressed(mouse_x, mouse_y, aGame);
        ++build_it;
    }
}
//------------------------------------------------------------------------------
// CHECK BULLETS COLLISIONS
//------------------------------------------------------------------------------
void Map::check_bullets_collisions() {
    vector<unsigned int> bullets_to_delete;
    map<unsigned int,ClientAmmo*>::iterator bullets_it = bullet_map.begin();
    while (bullets_it != bullet_map.end()) {
        ClientAmmo* bullet = bullets_it->second;
        unsigned int id = bullet->get_id();
        if (bullet->collisioned()) {
            if (!explosionExist(id)) {
                explosion_map.insert(pair<unsigned int, ClientExplosion*>
                                             (id, bullet->get_explosion(id)));
                bullets_to_delete.push_back(id);
            }
        }
        ++bullets_it;
    }
    if (bullets_to_delete.empty()) return;
    for (unsigned int i = 0 ; i < bullets_to_delete.size(); i++) {
        ClientAmmo* bullet = bullet_map.at(bullets_to_delete[i]);
        bullet_map.erase(bullet->get_id());
        delete bullet;
    }
    aGame.cleanMunitions();
}
//------------------------------------------------------------------------------
// HANDLE DEAD UNITS
//------------------------------------------------------------------------------
void Map::handle_dead_units(std::vector<Unit*>& dead_units) {
    if (dead_units.empty()) return;
    for (unsigned int i = 0; i < dead_units.size(); i++) {
        Unit* unit = dead_units[i];
        // Elimino cualquier bala que tuviera como target a la unidad que acaba
        // de morir
        unsigned int id = unit->get_id();
        map<unsigned int, ClientAmmo*>::iterator bullets_it;
        bullets_it = bullet_map.begin();
        while (bullets_it != bullet_map.end()) {
            ClientAmmo* bullet = bullets_it->second;
            unsigned int targetId = bullet->get_target()->get_id();
            unsigned int shooterId = bullet->get_shooter()->get_id();
            if (targetId == id) {
                bullet->target_died(unit);
                unit_stand_still(bullet->get_shooter()->get_id());
            }
            if (shooterId == id) {
                bullet->target_died(unit);
                unit_stand_still(bullet->getTargetId());
            }
            ++bullets_it;
        }
        units.erase(id);
        dead_units.erase(dead_units.begin()+i);
        delete unit;
    }
    aGame.cleanUnits();
}
//------------------------------------------------------------------------------
// HANDLE EXPLOSIONS
//------------------------------------------------------------------------------
void Map::handle_explosions(std::vector<ClientExplosion*>& explosions){
    for (unsigned int i = 0; i < explosions.size(); i++) {
        ClientExplosion* ptr = explosions[i];
        explosion_map.erase(ptr->get_id());
        explosions.erase(explosions.begin() + i);
        delete ptr;
    }
}
//------------------------------------------------------------------------------
// BUILDING SELECTED
//------------------------------------------------------------------------------
void Map::building_selected(unsigned int id, unsigned int player_id) {
    ClientBuilding* building =  buildings.at(id);
    if (building->get_owner_id() == player_id){
        building->show_interface();
    }
}
//------------------------------------------------------------------------------
// UNSELECTED BUILDING
//------------------------------------------------------------------------------
void Map::deselect_buildings() {
    map<unsigned int, ClientBuilding*>::iterator build_it = buildings.begin();
    while (build_it != buildings.end()) {
        build_it->second->hide_interface();
        ++build_it;
    }
}
//------------------------------------------------------------------------------
