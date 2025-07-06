#include "States.h"

void GroundTransfer4::initialize_impl() {
    ctx->intakeEEMotor.set(rollerGroundHandoffSpeed);
}

State* GroundTransfer4::loop_impl() {
    // adding a request removed here stops us from getting into an infinite loop
    if(ctx->groundSensor.getState() || requestRemoved){
        return new GroundTransfer5(this->ctx);
    }
    // if we time out, run through the other side
    if(this->currentTime >= handoffTimeout){
        return new EETransfer3(this->ctx);
    }
};
