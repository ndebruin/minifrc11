#include "States.h"

void L2Wait::initialize_impl() {}

State* L2Wait::loop_impl() {
    // if we're out of the area (assuming odom works)
    if(IsNotIn(&ctx->odomSensor, ReefArea)){
        return new L2Retract1(this->ctx);
    }
    // else, just use a timeout
    if(this->currentTime >= reefClearTimeout){
        return new L2Retract1(this->ctx);
    }

    return nullptr;
};
