#include "States.h"

void StowedEE::initialize_impl() {}

State* StowedEE::loop_impl() {
    

    // state transitions
    if(ctx->inputs.shouldExecute()){
        if(ctx->inputs.getGoal() == L1EE){
            return new L1EEDeploy1(this->ctx);
        }

        if(ctx->inputs.getGoal() == L2){
            return new L2Deploy1(this->ctx);
        }

        if(ctx->inputs.getGoal() == L3){
            return new L3Deploy1(this->ctx);
        }

        if(ctx->inputs.getGoal() == L4){
            return new L4Deploy1(this->ctx);
        }

        // if we need to switch to the end effector
        if(ctx->inputs.getGoal() == L1Ground){
            return new GroundTransfer1(this->ctx);
        }

        if(ctx->inputs.getGoal() == Climb){
            return new ClimbDeploy1(this->ctx);
        }

        if(ctx->inputs.getGoal() == DeAlgaefy){
            return new DeAlgaeDeploy1(this->ctx);
        }
    }

    // this cya's incase we missed something somehow
    if(ctx->groundSensor.getState()){
        return new StowedGround(this->ctx);
    }
    if(ctx->eeSensor.getState() == false){
        return new StowedEmpty(this->ctx);
    }
    
    return nullptr;
};
