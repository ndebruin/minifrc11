#include "States.h"

void L1EEWait::initialize_impl() {}

State* L1EEWait::loop_impl() {
    // if we're out of the area (assuming odom works)
    if(IsNotIn(&ctx->odomSensor, ReefArea)){
        return new L1EERetract1(this->ctx);
    }
    // else, just use a timeout
    if(this->currentTime >= reefClearTimeout){
        return new L1EERetract1(this->ctx);
    }
    
    return nullptr;
};
