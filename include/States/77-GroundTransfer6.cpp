#include "States.h"

void GroundTransfer6::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorBottomPosition);
}

State* GroundTransfer6::loop_impl() {
    if(this->currentTime >= elevatorDownTime){
        // verify that sensors are still right
        if(ctx->groundSensor.getState()){
            return new StowedGround(this->ctx);
        }
        if(ctx->eeSensor.getState()){
            return new StowedEE(this->ctx);
        }
        return new StowedEmpty(this->ctx);
    }

    return nullptr;
};
