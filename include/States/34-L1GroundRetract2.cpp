#include "States.h"

void L1GroundRetract2::initialize_impl() {
    ctx->intakeServo.write(intakeStowAngle);
}

State* L1GroundRetract2::loop_impl() {
    if(this->currentTime >= intakeRetractTime){
        return new L1GroundRetract3(this->ctx);
    }

    return nullptr;
};
