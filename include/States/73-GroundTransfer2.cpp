#include "States.h"

void GroundTransfer2::initialize_impl() {
    ctx->intakeServo.write(intakeHandoffAngle);
}

State* GroundTransfer2::loop_impl() {
    if(this->currentTime >= intakeHandoffTime){
        return new GroundTransfer3(this->ctx);
    }

    return nullptr;
};
