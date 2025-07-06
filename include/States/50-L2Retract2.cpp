#include "States.h"

void L2Retract2::initialize_impl() {
    ctx->armServo.write(armMiddleAngle);
}

State* L2Retract2::loop_impl() {
    if(this->currentTime >= armLowDownTime){
        return new L2Retract3(this->ctx);
    }

    return nullptr;
};
