#include "States.h"

void DeAlgaeDeployed::initialize_impl() {

}

State* DeAlgaeDeployed::loop_impl() {

    // safety timeout for if autoalign is messed up
    if(this->currentTime > autoAlignTimeout && !ctx->inputs.shouldExecute()){
        return new DeAlgaefy(this->ctx);
    }
    /* 
        kinda fake request "removed" here 
        bc we use the release of the trigger button
        to make it do the thing.
        this will be a common theme throughout the stateMachine,
        mainly for scoring
    */
    if(ctx->drivetrainController.inPosition() && !ctx->inputs.shouldExecute()){
        return new DeAlgaefy(this->ctx);
    }

    return nullptr;
};
