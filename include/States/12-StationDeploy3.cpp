#include "States.h"

void StationDeploy3::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorBottomPosition);
}

State* StationDeploy3::loop_impl() {
    if(this->currentTime >= elevatorDownTime){
        return new StationDeployed(this->ctx);
    }

    if(!ctx->inputs.shouldExecute()){
        return new StationRetract1(this->ctx);
    }
    
    return nullptr;
};
