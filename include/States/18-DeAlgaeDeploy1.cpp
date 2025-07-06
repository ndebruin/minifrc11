#include "States.h"

void DeAlgaeDeploy1::initialize_impl() {
    if(ctx->fieldPositionParser.algaeTarget() == L3){
        ctx->elevatorServo.writeMicroseconds(elevatorDeAlgaeL3Position);
    }
    ctx->AlgaeServo.write(algaeInitialDeployAngle);
    // ctx->drivetrainController.startAutoalign(Algae);
}

State* DeAlgaeDeploy1::loop_impl() {
    if(this->currentTime >= deAlgaeDeployTime){
        return new DeAlgaeDeployed(this->ctx);
    }

    if(requestRemoved){
        return new DeAlgaeRetract1(this->ctx);
    }
    
    return nullptr;
};
