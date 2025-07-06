#include "States.h"

void StationRetract2::initialize_impl() {
    ctx->armServo.write(armMiddleAngle);
}

State* StationRetract2::loop_impl() {
    if(this->currentTime >= armHighDownTime){
        return new StationRetract3(this->ctx);
    }

    return nullptr;
};
