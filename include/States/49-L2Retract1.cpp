#include "States.h"

void L2Retract1::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorClearEEPosition);
}

State* L2Retract1::loop_impl() {
    if(this->currentTime >= elevatorClearEETime){
        return new L2Retract2(this->ctx);
    }

    return nullptr;
};
