#include "States.h"

void GroundDeploy1::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorClearIntakePosition);
}

State* GroundDeploy1::loop_impl() {
    if(this->currentTime >=  elevatorClearIntakeTime){
        return new GroundDeploy2(this->ctx);
    }

    if(requestReleased){
        return new GroundRetract3(this->ctx);
    }
    
    return nullptr;
};
