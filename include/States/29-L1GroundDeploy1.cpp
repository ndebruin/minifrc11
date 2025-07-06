#include "States.h"

void L1GroundDeploy1::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorClearIntakePosition);
    // ctx->drivetrainController.startAutoalign(L1Ground);
}

State* L1GroundDeploy1::loop_impl() {
    if(this->currentTime >= elevatorClearIntakeTime){
        return new L1GroundDeploy2(this->ctx);
    }

    if(requestRemoved){
        return new L1GroundRetract3(this->ctx);
    }

    return nullptr;
};
