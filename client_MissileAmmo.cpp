#include "client_Ammo.h"
#include "client_MissileAmmo.h"
#include "client_GameObject.h"
#include "client_BigExplosion.h"
#include <iostream>
//------------------------------------------------------------------------------
// CLIENT MISSILE AMMO
//------------------------------------------------------------------------------
ClientMissileAmmo::ClientMissileAmmo(
        unsigned int bullet_id, Unit* shooter, GameObject* target):
        ClientAmmo(bullet_id, shooter, target) {
    x_frames.push_back(Frame("Units/Vehicles/MML/missile_0.png"));
    y_frames.push_back(Frame("Units/Vehicles/MML/missile_90.png"));
    xy_frames.push_back(Frame("Units/Vehicles/MML/missile_45.png"));
    xy_frames.push_back(Frame("Units/Vehicles/MML/missile_135.png"));
    current_frame = &xy_frames[0];
}
//------------------------------------------------------------------------------
// MOVE X
//------------------------------------------------------------------------------
void ClientMissileAmmo::move_x(unsigned int dest_x) {
    current_frame = &x_frames[0];
    ClientAmmo::move_x(dest_x);
}
//------------------------------------------------------------------------------
// MOVE Y
//------------------------------------------------------------------------------
void ClientMissileAmmo::move_y(unsigned int dest_y) {
    current_frame = &y_frames[0];
    ClientAmmo::move_y(dest_y);
}
//------------------------------------------------------------------------------
// MOVE XY
//------------------------------------------------------------------------------
void ClientMissileAmmo::move_xy(unsigned int dest_x, unsigned int dest_y) {
    if ((pos_x < dest_x && pos_y < dest_y)||(pos_x > dest_x && pos_y>dest_y)) {
        // diagonal hacia abajo y derecha
        if (frame_index < 1){
            frame_index = 1;
        }
    }

    if ((pos_x < dest_x && pos_y > dest_y)||(pos_x > dest_x && pos_y< dest_y)) {
        // diagonal hacia arriba y derecha
        if (frame_index > 0){
            frame_index = 0;
        }
    }
    current_frame = &xy_frames[frame_index];
    ClientAmmo::move_xy(dest_x, dest_y);
}
//------------------------------------------------------------------------------
// GET EXPLOSION
//------------------------------------------------------------------------------
ClientExplosion* ClientMissileAmmo::get_explosion(unsigned int id) {
    return new ClientBigExplosion(id, target_x, target_y);
}
//------------------------------------------------------------------------------
