#include "States.h"

void DeAlgaefy1::initialize_impl() {
    return;
}

State* DeAlgaefy1::loop_impl() {
    
    if(counter < deAlgaefyAttempts){
        if(ctx->AlgaeServo.getDegrees() == algaeInitialDeployAngle){
            counter++;
            ctx->AlgaeServo.write(algaeFinalDeployAngle);
        }
        else{
            ctx->AlgaeServo.write(algaeInitialDeployAngle);
        }
    }
    else{
        return new DeAlgaeRetract1(this->ctx);
    }
    
    return nullptr;
};
