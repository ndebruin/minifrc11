#include "States.h"

void L3Retract2::initialize_impl() {
    ctx->armServo.write(armMiddleAngle);
}

State* L3Retract2::loop_impl() {
    if(this->currentTime >= armHighDownTime){
        return new L3Retract3(this->ctx);
    }

    return nullptr;
};
