#include "States.h"

void L3Deploy2::initialize_impl() {
    ctx->armServo.write(armL3ReadyAngle);
}

State* L3Deploy2::loop_impl() {
    if(this->currentTime >= armL3Time){
        return new L3Deploy3(this->ctx);
    }

    if(requestRemoved){
        return new L3Retract2(this->ctx);
    }

    return nullptr;
};
