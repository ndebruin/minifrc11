#include "States.h"

void L1EEScore::initialize_impl() {
    ctx->intakeEEMotor.set(eeRollerL1ScoreSpeed);
    // ctx->driveTrainController.stopAutoalign();
}

State* L1EEScore::loop_impl() {
    // wait until sensor clear
    if(!ctx->eeSensor.getState()){
        return new L1EEWait(this->ctx);
    }

    // or until timeout
    if(this->currentTime >= armScoreTimeout){
        return new L1EEWait(this->ctx);
    }

    return nullptr;
};
