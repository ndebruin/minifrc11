#include "States.h"

void L4Retract3::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorBottomPosition);
}

State* L4Retract3::loop_impl() {
        if(this->currentTime >= elevatorL4Time){
        // check to see if we actually cleared
        if(ctx->eeSensor.getState()){
            return new StowedEE(this->ctx);
        }
        return new StowedEmpty(this->ctx);
    }

    return nullptr;
};
