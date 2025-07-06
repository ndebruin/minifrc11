#include "States.h"

void GroundRetract1::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorClearIntakePosition);
}

State* GroundRetract1::loop_impl() {
    if(this->currentTime >= elevatorClearIntakeTime){
        return new GroundRetract2(this->ctx);
    }

    return nullptr;    
};
