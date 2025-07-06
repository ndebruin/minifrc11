#include "States.h"

void EETransfer6::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorBottomPosition);
}

State* EETransfer6::loop_impl() {
    if(this->currentTime >= elevatorDownTime){
        // verify that sensors are still right
        if(ctx->eeSensor.getState()){
            return new StowedEE(this->ctx);
        }
        if(ctx->groundSensor.getState()){
            return new StowedGround(this->ctx);
        }
        return new StowedEmpty(this->ctx);
    }

    return nullptr;
};
