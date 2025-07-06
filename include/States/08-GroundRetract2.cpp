#include "States.h"

void GroundRetract2::initialize_impl() {
    ctx->intakeServo.write(intakeStowAngle);
}

State* GroundRetract2::loop_impl() {
    if(this->currentTime >= intakeRetractTime){
        return new GroundRetract2(this->ctx);
    }

    return nullptr;  
};
