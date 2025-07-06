#include "States.h"

void L1GroundDeploy2::initialize_impl() {
    ctx->intakeServo.write(intakeL1ReadyAngle);
}

State* L1GroundDeploy2::loop_impl() {
    if(this->currentTime >= intakeDeployTime){
        return new L1GroundDeploy3(this->ctx);
    }

    if(!ctx->inputs.shouldExecute()){
        return new L1GroundRetract2(this->ctx);
    }
    
    return nullptr;
};
