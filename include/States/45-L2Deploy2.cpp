#include "States.h"

void L2Deploy2::initialize_impl() {
    ctx->armServo.write(armL2ReadyAngle);
}

State* L2Deploy2::loop_impl() {
    if(this->currentTime >= armL2Time){
        return new L2Deploy3(this->ctx);
    }

    if(requestRemoved){
        return new L2Retract2(this->ctx);
    }

    return nullptr;
};
