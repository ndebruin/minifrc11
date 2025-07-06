#include "States.h"

void L4Deploy2::initialize_impl() {
    ctx->armServo.write(armL4ReadyAngle);
}

State* L4Deploy2::loop_impl() {
    /* 
        kinda fake request "removed" here 
        bc we use the release of the trigger button
        to make it do the thing.
        this will be a common theme throughout the stateMachine,
        mainly for scoring
    */

    // safety timeout for if autoalign is messed up
    if(this->currentTime >= autoAlignTimeout && !ctx->inputs.shouldExecute()){
        return new L4Score(this->ctx);
    }

    
    if(ctx->drivetrainController.inPosition() FULL_AUTO !ctx->inputs.shouldExecute()){
        return new L4Score(this->ctx);
    }

    return nullptr;
};
