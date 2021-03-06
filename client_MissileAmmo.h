#ifndef CLIENT_MISSILEAMMO_H_INCLUDED
#define CLIENT_MISSILEAMMO_H_INCLUDED
//------------------------------------------------------------------------------
#include "client_Ammo.h"
//------------------------------------------------------------------------------
class ClientMissileAmmo: public ClientAmmo {
 private :
    //--------------------------------------------------------------------------
    // Alterna los fotogramas de la bala moviendose en horizontal
    void move_x(unsigned int dest_x);
    //--------------------------------------------------------------------------
    // Alterna los fotogramas de la bala moviendose en vertical
    void move_y(unsigned int dest_y);
    //--------------------------------------------------------------------------
    // Alterna los fotogramas de la bala moviendose en diagonal
    void move_xy(unsigned int dest_x, unsigned int dest_y);
    //--------------------------------------------------------------------------
 public :
    //--------------------------------------------------------------------------
    ClientMissileAmmo(unsigned int id, Unit* shooter, GameObject* target);
    //--------------------------------------------------------------------------
    ClientExplosion* get_explosion(unsigned int get_explosion);
    //--------------------------------------------------------------------------
};
#endif // CLIENT_MISSILEAMMO_H_INCLUDED
