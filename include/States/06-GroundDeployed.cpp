#include "States.h"

void GroundDeployed::initialize_impl() {
    ctx->intakeEEMotor.set(intakeRollerIntakeSpeed);
}

State* GroundDeployed::loop_impl() {

    if(ctx->groundSensor.getState()){
        return new GroundRetract1(this->ctx);
    }

    if(!ctx->inputs.shouldExecute()){
        return new GroundRetract1(this->ctx);
    }

    return nullptr;
};
