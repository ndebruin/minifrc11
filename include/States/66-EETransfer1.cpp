#include "States.h"

void EETransfer1::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorHandoffLowPosition);
}

State* EETransfer1::loop_impl() {
    if(this->currentTime >= elevatorClearIntakeTime){
        return new EETransfer2(this->ctx);
    }

    return nullptr;
};
