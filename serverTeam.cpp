// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#include "serverTeam.h"
#include "serverPlayer.h"
//------------------------------------------------------------------------------
// PLAYER CONSTRUCTOR
//------------------------------------------------------------------------------
ServerTeam::ServerTeam(const size_t id): id(id) {}
//------------------------------------------------------------------------------
// PLAYER DESTRUCTOR
//------------------------------------------------------------------------------
ServerTeam::~ServerTeam() {}
//------------------------------------------------------------------------------
// GET ID
//------------------------------------------------------------------------------
const size_t& ServerTeam::getId() const {
    return id;
}
//------------------------------------------------------------------------------
// ADD PLAYER
//------------------------------------------------------------------------------
void ServerTeam::addPlayer(ServerPlayer &aPlayer) {
    playersTeam(aPlayer.getId(), &aPlayer);
    aPlayer.addTeam(*this);
}
//------------------------------------------------------------------------------
// ADD PLAYER
//------------------------------------------------------------------------------
void ServerTeam::erasePlayer(size_t idPlayer) {
    playersTeam.erase(idPlayer);
}
//------------------------------------------------------------------------------
// BELONGS
//------------------------------------------------------------------------------
bool ServerTeam::belongs(const ServerPlayer& aPlayer) const {
    return playersTeam.keyExist(aPlayer.getId());
}
//------------------------------------------------------------------------------
// HAS LOST
//------------------------------------------------------------------------------
bool ServerTeam::hasLost() {
    for (ServerPlayer* aPlayer : playersTeam.getList()) {
        if (!aPlayer->hasLost()) return false;
    }
    return true;
}
//------------------------------------------------------------------------------