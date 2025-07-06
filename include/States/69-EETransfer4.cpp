#include "States.h"

void EETransfer4::initialize_impl() {
    ctx->intakeEEMotor.set(0.0);
    ctx->elevatorServo.writeMicroseconds(elevatorHandoffHighPosition);
}

State* EETransfer4::loop_impl() {
    if(this->currentTime >= elevatorClearIntakeTime){
        return new EETransfer5(this->ctx);
    }

    return nullptr;
};
