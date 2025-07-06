#include "States.h"

void L1EEDeploy1::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorClearEEPosition);
    // ctx->driveTrainController.startAutoalign(L1EE);
}

State* L1EEDeploy1::loop_impl() {
    if(this->currentTime >= elevatorClearEETime){
        return new L1EEDeploy2(this->ctx);
    }

    if(!ctx->inputs.shouldExecute()){
        return new L1EERetract3(this->ctx);
    }

    return nullptr;
};
