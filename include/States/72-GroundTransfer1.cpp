#include "States.h"

void GroundTransfer1::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorHandoffHighPosition);
}

State* GroundTransfer1::loop_impl() {
    if(this->currentTime >= elevatorClearIntakeTime){
        return new GroundTransfer2(this->ctx);
    }

    return nullptr;
};
