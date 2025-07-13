#include "States.h"

void L1GroundDeploy3::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorBottomPosition);
}

State* L1GroundDeploy3::loop_impl() {
    /* 
        kinda fake request "removed" here 
        bc we use the release of the trigger button
        to make it do the thing.
        this will be a common theme throughout the stateMachine,
        mainly for scoring
    */

    // safety timeout for if autoalign is messed up
    if(this->currentTime >= autoAlignTimeout && !ctx->inputs.shouldExecute()){
        return new L1EEScore(this->ctx);
    }

    
    // if(ctx->drivetrainController.inPosition() && !ctx->inputs.shouldExecute()){
    //     return new L1EEScore(this->ctx);
    // }

    return nullptr;
};
