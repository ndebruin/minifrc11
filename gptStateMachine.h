#ifndef STATE_H
#define STATE_H

class StateMachine; // Forward declaration

class State {
public:
    virtual ~State() {}
    virtual void enter(StateMachine* fsm) = 0;
    virtual void update(StateMachine* fsm) = 0;
    virtual void exit(StateMachine* fsm) = 0;
};

#endif


#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "State.h"

class StateMachine {
private:
    State* currentState;
    State* defaultState;  // For reset
public:
    StateMachine(State* initialState);
    void update();
    void changeState(State* newState);
    void reset();

    State* getState();
};

#endif



#include "StateMachine.h"

StateMachine::StateMachine(State* initialState)
    : currentState(initialState), defaultState(initialState) {
    currentState->enter(this);
}

void StateMachine::update() {
    if (currentState) currentState->update(this);
}

void StateMachine::changeState(State* newState) {
    if (currentState) currentState->exit(this);
    currentState = newState;
    if (currentState) currentState->enter(this);
}

void StateMachine::reset() {
    changeState(defaultState);
}

State* StateMachine::getState() {
    return currentState;
}



#ifndef IDLESTATE_H
#define IDLESTATE_H

#include "State.h"

class IdleState : public State {
public:
    void enter(StateMachine* fsm) override;
    void update(StateMachine* fsm) override;
    void exit(StateMachine* fsm) override;
};

#endif

#include "IdleState.h"
#include "StateMachine.h"
#include "MoveState.h" // Example transition

void IdleState::enter(StateMachine* fsm) {
    Serial.println("Entering Idle State");
}

void IdleState::update(StateMachine* fsm) {
    // Example transition logic
    if (/* condition to move */) {
        static MoveState moveState;
        fsm->changeState(&moveState);
    }
}

void IdleState::exit(StateMachine* fsm) {
    Serial.println("Exiting Idle State");
}

#include "StateMachine.h"
#include "IdleState.h"

IdleState idleState;
StateMachine fsm(&idleState);

void setup() {
    Serial.begin(9600);
}

void loop() {
    fsm.update();

    // Optional reset logic
    if (/* reset condition */) {
        fsm.reset();
    }

    delay(10);
}

