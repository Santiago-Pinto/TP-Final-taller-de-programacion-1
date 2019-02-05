#include "client_Territory.h"
#include "client_Tile.h"
#include "client_Building.h"
#include "client_TerrainObject.h"
#include <vector>
#include <iostream>
using std::vector;

Territory::Territory(std::vector<Tile*>& tiles):
  tiles(std::move(tiles)){
}

void Territory::draw(SDL_Surface* surface, ClientCamera& camera){
    std::vector<Tile*>::iterator tiles_it = tiles.begin();
    while (tiles_it != tiles.end()){
        (*tiles_it)->draw(surface, camera);
        tiles_it++;
    }
}

Territory::~Territory(){
     std::vector<Tile*>::iterator tile_it = tiles.begin();
     while (tile_it != tiles.end()){
        delete (*tile_it);
        ++tile_it;
     }
}
