#include "States.h"

void L1EERetract3::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorBottomPosition);
}

State* L1EERetract3::loop_impl() {
    if(this->currentTime >= elevatorDownTime){
        // check to see if we actually cleared
        if(ctx->eeSensor.getState()){
            return new StowedEE(this->ctx);
        }
        return new StowedEmpty(this->ctx);
    }

    return nullptr;
};
