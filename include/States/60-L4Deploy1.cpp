#include "States.h"

void L4Deploy1::initialize_impl() {
    ctx->elevatorServo.writeMicroseconds(elevatorL4Position);
}

State* L4Deploy1::loop_impl() {
    if(this->currentTime >= elevatorL4Time){
        return new L4Deploy2(this->ctx);
    }

    if(requestRemoved){
        return new L4Retract3(this->ctx);
    }
    
    return nullptr;
};
