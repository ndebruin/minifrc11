#include "States.h"

void StowedGround::initialize_impl() {
    return;
}

State* StowedGround::loop_impl() {
    
    // state transitions
    if(ctx->inputs.shouldExecute()){
        if(ctx->inputs.getGoal() == L1Ground){
            return new L1GroundDeploy1(this->ctx);
        }

        // if we need to switch to the end effector
        if(ctx->inputs.getGoal() == L1EE || ctx->inputs.getGoal() == L2 || ctx->inputs.getGoal() == L3 || ctx->inputs.getGoal() == L4){
            return new EETransfer1(this->ctx);
        }

        if(ctx->inputs.getGoal() == Climb){
            return new ClimbDeploy1(this->ctx);
        }

        if(ctx->inputs.getGoal() == DeAlgaefy){
            return new DeAlgaeDeploy1(this->ctx);
        }
    }
    
    // this cya's incase we missed something somehow
    if(ctx->eeSensor.getState()){
        return new StowedEE(this->ctx);
    }
    if(ctx->groundSensor.getState() == false){
        return new StowedEmpty(this->ctx);
    }
    
    return nullptr;
};
