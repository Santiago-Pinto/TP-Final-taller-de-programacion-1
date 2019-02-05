#include "client_ShootAction.h"
#include "client_Unit.h"
#include "client_Ammo.h"
ShootAction::ShootAction(Unit* unit,GameObject* target):
   UnitAction(unit), target(target){
}

void ShootAction::execute(){
    if (unit != nullptr){
      this->unit->shoot(target);
    }
}

void ShootAction::finish(){
}
