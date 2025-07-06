#include "States.h"

void L2Deploy1::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorClearEEPosition);
    // TO:DO: add autoalign start based on which trigger pressed
}

State* L2Deploy1::loop_impl() {
    if(this->currentTime >= elevatorClearEETime){
        return new L2Deploy2(this->ctx);
    }

    if(requestRemoved){
        return new L2Retract3(this->ctx);
    }
    
    return nullptr;
};
