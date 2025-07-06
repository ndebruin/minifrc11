#include "States.h"

void L3Wait::initialize_impl() {}

State* L3Wait::loop_impl() {
    // if we're out of the area (assuming odom works)
    if(IsNotIn(&ctx->odomSensor, ReefArea)){
        return new L3Retract1(this->ctx);
    }
    // else, just use a timeout
    if(this->currentTime >= reefClearTimeout){
        return new L3Retract1(this->ctx);
    }

    return nullptr;
};
