#include "States.h"

void DeAlgaefy::initialize_impl() {}

State* DeAlgaefy::loop_impl() {
    
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
