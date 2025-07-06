#include "States.h"

void StationDeploy1::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorClearEEPosition);
    // ctx->driveTrainController.startAutoalign(CoralStation);
}

State* StationDeploy1::loop_impl() {
    if(this->currentTime >= elevatorClearEETime){
        return new StationDeploy2(this->ctx);
    }

    if(requestReleased){
        return new StationRetract3(this->ctx);
    }
    
    return nullptr;
};
