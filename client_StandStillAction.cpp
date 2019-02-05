#include "client_UnitAction.h"
#include "client_WalkAction.h"
#include "client_Unit.h"
#include "client_StandStillAction.h"

StandStillAction::StandStillAction(Unit* unit):
   UnitAction(unit){
}

void StandStillAction::execute() {
    if (unit != nullptr){
        this->unit->stand_still();
    }
}

void StandStillAction::finish() {
    //no hace nada
}
