#include "States.h"

void StowedEmpty::initialize_impl() {}// not doing anything in this case, but would otherwise move actuators in this part
    

State* StowedEmpty::loop_impl() {
    
    if(groundIntakeRequest){
        return new GroundDeploy1(this->ctx);
    }

    if(StationIntakeRequest){
        return new StationDeploy1(this->ctx);
    }

    if(climbRequest){
        return new ClimbDeploy1(this->ctx);
    }

    if(deAlgaeRequest){
        return new DeAlgaeDeploy1(this->ctx);
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
