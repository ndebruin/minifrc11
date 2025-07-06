#include "States.h"

void StowedEmpty::initialize_impl() {}// not doing anything in this case, but would otherwise move actuators in this part
    

State* StowedEmpty::loop_impl() {
    
    // state transitions
    if(ctx->inputs.shouldExecute()){
        if(ctx->inputs.getGoal() == GroundIntake){
            return new GroundDeploy1(this->ctx);
        }

        if(ctx->inputs.getGoal() == StationIntake){
            return new StationDeploy1(this->ctx);
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
    if(ctx->eeSensor.getState()){
        return new StowedEE(this->ctx);
    }
    
    
    return nullptr;
};
