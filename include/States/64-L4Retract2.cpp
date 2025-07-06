#include "States.h"

void L4Retract2::initialize_impl() {
    ctx->armServo.write(armMiddleAngle);
}

State* L4Retract2::loop_impl() {
    if(this->currentTime >= armHighDownTime){
        return new L4Retract3(this->ctx);
    }

    return nullptr;
};
