#include "States.h"

void L1EEDeploy3::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorBottomPosition);
}

State* L1EEDeploy3::loop_impl() {
    /* 
        kinda fake request "removed" here 
        bc we use the release of the trigger button
        to make it do the thing.
        this will be a common theme throughout the stateMachine,
        mainly for scoring
    */

    // safety timeout for if autoalign is messed up
    if(this->currentTime >= autoAlignTimeout && requestRemoved){
        return new L1GroundScore(this->ctx);
    }

    
    if(ctx->drivetrainController.inPosition() && requestRemoved){
        return new L1GroundScore(this->ctx);
    }

    return nullptr;
};
