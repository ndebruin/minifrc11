#include "States.h"

void L3Score::initialize_impl() {
    ctx->armServo.write(armL3ScoreAngle);
    ctx->driveTrainController.stopAutoAlign();
}

State* L3Score::loop_impl() {
    // wait until sensor clear
    if(!ctx->eeSensor.getState()){
        return new L3Wait(this->ctx);
    }

    // or until timeout
    if(this->currentTime >= armScoreTimeout){
        return new L3Wait(this->ctx);
    }
    
    return nullptr;
};
