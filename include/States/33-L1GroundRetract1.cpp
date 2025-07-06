#include "States.h"

void L1GroundRetract1::initialize_impl() {
    ctx->intakeEEMotor.set(0.0);
    ctx->elevatorServo.writeMicroseconds(elevatorClearIntakePosition);
}

State* L1GroundRetract1::loop_impl() {
    if(this->currentTime >= elevatorClearIntakeTime){
        return new L1GroundRetract2(this->ctx);
    }

    return nullptr;
};
