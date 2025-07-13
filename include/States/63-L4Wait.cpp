#include "States.h"

void L4Wait::initialize_impl() {
    return;
}

State* L4Wait::loop_impl() {
    // if we're out of the area (assuming odom works)
    // if(IsNotIn(&ctx->odomSensor, ReefArea)){
    //     return new L4Retract2(this->ctx);
    // }
    // else, just use a timeout
    if(this->currentTime >= reefClearTimeout){
        return new L4Retract2(this->ctx);
    }

    return nullptr;
};
