#include "States.h"

void StationDeploy2::initialize_impl() {
    ctx->armServo.write(armBackwardStationIntakeAngle);
}

State* StationDeploy2::loop_impl() {
    if(this->currentTime >= armStationIntakeTime){
        return new StationDeploy3(this->ctx);
    }

    if(!ctx->inputs.shouldExecute()){
        return new StationRetract2(this->ctx);
    }
    
    return nullptr;
};
