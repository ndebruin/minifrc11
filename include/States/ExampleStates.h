#pragma once

#include "../Context.h"
#include "../boilerplate/StateMachine/State.h"
#include "../boilerplate/StateMachine/StateMachine.h"
#include "../boilerplate/Utilities/Debouncer.h"
// #include "FlightParams.h"
#include "../boilerplate/Utilities/RunningExpAverage.h"
#include "../boilerplate/Utilities/TimeAverage.h"
#include <Arduino.h>

enum StateId {
    ID_PreLaunch,
    ID_Boost,
    ID_Coast,
    ID_DrogueDescent,
    ID_MainDescent,
    ID_Recovery,
    ID_Abort
};

using State = TState<Context, StateId, decltype(&millis)>;
using StateMachine = TStateMachine<Context, StateId, decltype(&millis)>;

#define STATE_INNER(name)                                                      \
  public:                                                                      \
    name(Context *ctx) : State(ID_##name, ::millis, ctx) {}                    \
                                                                               \
  private:                                                                     \
    void initialize_impl() override;                                           \
    State *loop_impl() override;

class PreLaunch : public State {
    STATE_INNER(PreLaunch)

    Debouncer accelDebouncer = Debouncer(500);
    uint32_t lastAccelReadingTime = 0;
    TimeAverage<float, 50> altAverager{};
    uint32_t lastBaroReadingTime = 0;
    bool savedInitialAltitude = false;
};

class Boost : public State {
    STATE_INNER(Boost)

    Debouncer accelDebouncer = Debouncer(100);
    uint32_t lastAccelReadingTime = 0;
};

class Coast : public State {
    STATE_INNER(Coast)

    // FIXME: probably way to big
    RunningExpAverage<float> ewma{0.3};
    bool firstVelCalculated = false;
    float prevAltitude = 0;
    Debouncer velDebouncer = Debouncer(100);
    uint32_t lastBaroReadingTime = 0;
};

class DrogueDescent : public State {
    STATE_INNER(DrogueDescent)

    RunningExpAverage<float> ewma{0.3};
    float prevAltitude = 0;
    bool firstVelCalculated = false;
    Debouncer velDebouncer = Debouncer(50);
    uint32_t lastBaroReadingTime = 0;
};

class MainDescent : public State {
    STATE_INNER(MainDescent)

    RunningExpAverage<float> ewma{0.1};
    float prevAltitude = 0;
    bool firstVelCalculated = false;
    Debouncer velDebouncer = Debouncer(50);
    uint32_t lastBaroReadingTime = 0;
};

class Recovery : public State {
    STATE_INNER(Recovery)
};

class Abort : public State {
    STATE_INNER(Abort)
};