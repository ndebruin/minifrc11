#include "States.h"

void GroundTransfer5::initialize_impl() {
    ctx->intakeEEMotor.set(0.0);
    ctx->intakeServo.write(intakeStowAngle);
}

State* GroundTransfer5::loop_impl() {
    if(this->currentTime >= intakeHandoffTime){
        return new GroundTransfer6(this->ctx);
    }

    return nullptr;
};
