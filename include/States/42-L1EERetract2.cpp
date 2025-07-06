#include "States.h"

void L1EERetract2::initialize_impl() {
    ctx->armServo.write(armMiddleAngle);
}

State* L1EERetract2::loop_impl() {
    if(this->currentTime >= armLowDownTime){
        return new L1EERetract3(this->ctx);
    }

    return nullptr;
};
