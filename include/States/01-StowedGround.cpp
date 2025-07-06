#include "States.h"

void StowedGround::initialize_impl() {}

State* StowedGround::loop_impl() {
    
    if(L1GroundRequest){
        return new L1GroundDeploy1(this->ctx);
    }

    if(EEScoreRequest){
        return new EETransfer1(this->ctx);
    }
    
    if(climbRequest){
        return new ClimbDeploy1(this->ctx);
    }

    if(deAlgaeRequest){
        return new DeAlgaeDeploy1(this->ctx);
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
