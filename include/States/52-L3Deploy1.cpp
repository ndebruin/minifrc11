#include "States.h"

void L3Deploy1::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorClearEEPosition);
}

State* L3Deploy1::loop_impl() {
    if(this->currentTime >= elevatorClearEETime){
        return new L3Deploy2(this->ctx);
    }

    if(requestRemoved){
        return new L3Retract3(this->ctx);
    }
    
    return nullptr;
};
