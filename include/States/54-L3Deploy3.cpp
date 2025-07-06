#include "States.h"

void L3Deploy3::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorBottomPosition);
}

State* L3Deploy3::loop_impl() {
    /* 
        kinda fake request "removed" here 
        bc we use the release of the trigger button
        to make it do the thing.
        this will be a common theme throughout the stateMachine,
        mainly for scoring
    */

    // safety timeout for if autoalign is messed up
    if(this->currentTime >= autoAlignTimeout && requestRemoved){
        return new L3Score(this->ctx);
    }

    
    if(ctx->drivetrainController.inPosition() FULL_AUTO requestRemoved){
        return new L3Score(this->ctx);
    }

    return nullptr;
};
