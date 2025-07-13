#include "States.h"

void L1EEDeploy2::initialize_impl() {
    ctx->armServo.write(armL1FowardAngle);
}

State* L1EEDeploy2::loop_impl() {
    if(this->currentTime >= armL1Time){
        return new L1EEDeploy3(this->ctx);
    }

    if(!ctx->inputs.shouldExecute()){
        return new L1EERetract2(this->ctx);
    }

    return nullptr;
};
