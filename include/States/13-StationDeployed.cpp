#include "States.h"

void StationDeployed::initialize_impl() {
    ctx->intakeEEMotor.set(eeRollerIntakeSpeed);
}

State* StationDeployed::loop_impl() {
    if(ctx->eeSensor.getState()){
        return new StationWait(this->ctx);
    }
    if(requestRemoved){
        return new StationWait(this->ctx);
    }

    return nullptr;
};
