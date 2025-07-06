#include "States.h"

void EETransfer5::initialize_impl() {
    ctx->intakeServo.write(intakeStowAngle);
}

State* EETransfer5::loop_impl() {
    if(this->currentTime >= intakeHandoffTime){
        return new EETransfer6(this->ctx);
    }

    return nullptr;
};
