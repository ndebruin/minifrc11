#include "States.h"

void L1EERetract1::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorClearEEPosition);
}

State* L1EERetract1::loop_impl() {
    if(this->currentTime >= elevatorClearEETime){
        return new L1EERetract2(this->ctx);
    }
    
    return nullptr;
};
