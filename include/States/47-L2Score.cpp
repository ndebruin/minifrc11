#include "States.h"

void L2Score::initialize_impl() {
    ctx->armServo.write(armL2ForwardScoreAngle);
    // ctx->driveTrainController.stopAutoalign();
}

State* L2Score::loop_impl() {
    // wait until sensor clear
    if(!ctx->eeSensor.getState()){
        return new L2Wait(this->ctx);
    }

    // or until timeout
    if(this->currentTime >= armScoreTimeout){
        return new L2Wait(this->ctx);
    }
    
    return nullptr;
};
