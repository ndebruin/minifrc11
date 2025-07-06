#include "States.h"

void L1GroundScore::initialize_impl() {
    ctx->intakeServo.write(intakeL1ScoreAngle);
    ctx->intakeEEMotor.set(intakeRollerL1ScoreSpeed);
    ctx->drivetrainController.stopAutoalign();
}

State* L1GroundScore::loop_impl() {
    // wait until sensor clear
    if(!ctx->groundSensor.getState()){
        return new L1GroundRetract1(this->ctx);
    }

    // or until timeout
    if(this->currentTime >= intakeScoreTimeout){
        return new L1GroundRetract1(this->ctx);
    }

    return nullptr;
};
