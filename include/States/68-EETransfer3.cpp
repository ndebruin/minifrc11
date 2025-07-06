#include "States.h"

void EETransfer3::initialize_impl() {
    ctx->intakeEEMotor.set(rollerEEHandoffSpeed);
}

State* EETransfer3::loop_impl() {
    // if we've passed off sucessfully
    // adding a removedRequest here stops us from infinite loop
    if(ctx->eeSensor.getState() || requestRemoved){
        return new EETransfer4(this->ctx);
    }
    if(this->currentTime >= handoffTimeout){
        return new GroundTransfer4(this->ctx);
    }

    return nullptr;
};
