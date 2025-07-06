#include "States.h"

void L1GroundRetract3::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorBottomPosition);
}

State* L1GroundRetract3::loop_impl() {
    if(this->currentTime >= elevatorDownTime){
        // check to see if we actually cleared
        if(ctx->groundSensor.getState()){
            return new StowedGround(this->ctx);
        }
        return new StowedEmpty(this->ctx);
    }
    
    return nullptr;
};
