#include "States.h"

void StationWait::initialize_impl() {}

State* StationWait::loop_impl() {
    // if we're out of the area (assuming odom works)
    if(IsNotIn(&ctx->odomSensor, StationIntakeArea)){
        return new StationRetract1(this->ctx);
    }
    // else, just use a timeout
    if(this->currentTime >= stationClearTimeout){
        return new StationRetract1(this->ctx);
    }
    
    return nullptr;
};
