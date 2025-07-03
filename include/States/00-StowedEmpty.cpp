#include "States.h"

void StowedEmpty::initialize_impl() {}

State* StowedEmpty::loop_impl() {
    
    ctx->AlgaeServo.write(0.5); // example of driving actuators

    // example delay thing
    // this doesn't do any amount of real delay, but once we've in this state for 1 second it will transition
    if(this->currentTime > 1000){
        return new NewState(ctx);
    }
    
    return nullptr;
};