#include "States.h"

void GroundDeploy3::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorBottomPosition);
}

State* GroundDeploy3::loop_impl() {
    if(this->currentTime >=  elevatorDownTime){
        return new GroundDeployed(this->ctx);
    }

    if(!ctx->inputs.shouldExecute()){
        return new GroundRetract1(this->ctx);
    }

    return nullptr;
};
