#include "States.h"

void GroundDeploy2::initialize_impl() {
    ctx->intakeServo.write(intakeDeployAngle);
}

State* GroundDeploy2::loop_impl() {
    if(this->currentTime >=  intakeDeployTime){
        return new GroundDeploy3(this->ctx);
    }

    if(requestReleased){
        return new GroundRetract2(this->ctx);
    }

    return nullptr;
};
