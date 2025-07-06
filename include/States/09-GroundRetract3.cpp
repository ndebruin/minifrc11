#include "States.h"

void GroundRetract3::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorBottomPosition);
}

State* GroundRetract3::loop_impl() {
    // wait until the elevator is down before we make a decision
    if(this->currentTime >= elevatorDownTime){
        // if we have a coral
        if(ctx->groundSensor.getState()){
            return new StowedGround(this->ctx);
        }
        return new StowedEmpty(this->ctx);
    }
    return nullptr;
    
};
