#include "States.h"

void L3Retract1::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorClearEEPosition);
}

State* L3Retract1::loop_impl() {
    if(this->currentTime >= elevatorClearEETime){
        return new L3Retract2(this->ctx);
    }

    return nullptr;
};
