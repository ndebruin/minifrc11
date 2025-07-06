#include "States.h"

void GroundTransfer3::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorHandoffLowPosition);
}

State* GroundTransfer3::loop_impl() {
    if(this->currentTime >= elevatorDownTime){
        return new GroundTransfer4(this->ctx);
    }
    
    return nullptr;
};
