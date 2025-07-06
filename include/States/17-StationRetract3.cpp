#include "States.h"

void StationRetract3::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorBottomPosition);
}

State* StationRetract3::loop_impl() {
    // wait until the elevator is down before we make a decision
    if(this->currentTime >= elevatorDownTime){
        // if we have a coral
        if(ctx->eeSensor.getState()){
            return new StowedEE(this->ctx);
        }
        return new StowedEmpty(this->ctx);
    }
    return nullptr;
};
