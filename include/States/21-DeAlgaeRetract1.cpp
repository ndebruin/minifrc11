#include "States.h"

void DeAlgaeRetract1::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorBottomPosition);
    ctx->AlgaeServo.write(algaeStowAngle);
    ctx->drivetrainController.stopAutoalign();
}

State* DeAlgaeRetract1::loop_impl() {
    #if elevatorDownTime > deAlgaeRetractTime
    if(this->currentTime >= elevatorDownTime)
    #else
    if(this->currentTime >= deAlgaeRetractTime)
    #endif
    {
        if(ctx->eeSensor.getState()){
            return new StowedEE(this->ctx);
        }
        if(ctx->groundSensor.getState()){
            return new StowedGround(this->ctx);
        }
        return new StowedEmpty(this->ctx);
    }
    
    return nullptr;    
};
