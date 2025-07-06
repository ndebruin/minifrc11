#include "States.h"

void L4Score::initialize_impl() {
    ctx->armServo.write(armL4ScoreAngle);
    ctx->driveTrainController.stopAutoAlign();
}

State* L4Score::loop_impl() {
    // wait until sensor clear
    if(!ctx->eeSensor.getState()){
        return new L4Wait(this->ctx);
    }

    // or until timeout
    if(this->currentTime >= armScoreTimeout){
        return new L4Wait(this->ctx);
    }
    
    return nullptr;
};
