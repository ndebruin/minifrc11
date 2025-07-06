#include "States.h"

void StationRetract1::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorClearEEPosition);
}

State* StationRetract1::loop_impl() {
    if(this->currentTime >= elevatorClearEETime){
        return new StationRetract2(this->ctx);
    }

    return nullptr;
};
