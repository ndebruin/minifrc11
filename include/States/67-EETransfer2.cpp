#include "States.h"

void EETransfer2::initialize_impl() {
    ctx->intakeServo.write(intakeHandoffAngle);
}

State* EETransfer2::loop_impl() {
    if(this->currentTime >= intakeHandoffTime){
        return new EETransfer3(this->ctx);
    }

    return nullptr;
};
