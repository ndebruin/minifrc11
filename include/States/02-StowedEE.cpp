#include "States.h"

void StowedEE::initialize_impl() {}

State* StowedEE::loop_impl() {
    
    if(L1EEScoreRequest){
        return new L1EEDeploy1(this->ctx);
    }

    if(L2ScoreRequest){
        return new L2Deploy1(this->ctx);
    }

    if(L3ScoreRequest){
        return new L3Deploy1(this->ctx);
    }

    if(L4ScoreRequest){
        return new L4Deploy1(this->ctx);
    }
    
    if(L1GroundRequest){
        return new GroundTransfer1(this->ctx);
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
    if(ctx->eeSensor.getState() == false){
        return new StowedEmpty(this->ctx);
    }
    
    return nullptr;
};
