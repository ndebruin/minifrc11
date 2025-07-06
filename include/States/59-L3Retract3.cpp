#include "States.h"

void L3Retract3::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorBottomPosition);
}

State* L3Retract3::loop_impl() {
    if(this->currentTime >= elevatorDownTime){
        // check to see if we actually cleared
        if(ctx->eeSensor.getState()){
            return new StowedEE(this->ctx);
        }
        return new StowedEmpty(this->ctx);
    }

    return nullptr;
};
