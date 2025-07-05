#pragma once

#include "../Context.h"
#include "../../boilerplate/StateMachine/State.h"
#include "../../boilerplate/StateMachine/StateMachine.h"
#include <Arduino.h>

enum StateId {
    /* 
    in almost all cases, in the event of a removed request,
    we just go from the Deploy# state to the inverse Retract# state.
    */

    // stowed states
    ID_StowedEmpty, // passes to either intake, or to climb/dealgae
    ID_StowedGround, // passes to L1 Ground, StowedEE, or climb/deAlgae
    ID_StowedEE, // passes to all EE scoring, StowedGround, or climb/deAlgae

    // ground intake states
    ID_GroundDeploy1, // elevator up to clear intake, time delay
    ID_GroundDeploy2, // intake out, time delay
    ID_GroundDeploy3, // elevator down, time delay
    ID_GroundDeployed, // start roller, time delay // once sensor or removed request, move forward
    ID_GroundRetract1, // elevator up & stop roller
    ID_GroundRetract2, // intake in, time delay
    ID_GroundRetract3, // elevator down, 
    // if no coral, move to stowedEmpty, otherwise move to StowedGround

    // station intake states
    ID_StationDeploy1, // elevator up to clear intake & start autoalign, time delay
    ID_StationDeploy2, // arm out, time delay
    ID_StationDeploy3, // elevator down, move foward when autoalign good / request removed
    ID_StationDeployed, // stop autoalign, start roller, time delay, wait for piece / removed request
    ID_StationWait, // wait until arm clear of station, odom
    ID_StationRetract1, // elevator up to clear intake, time delay
    ID_StationRetract2, // arm down, time delay
    ID_StationRetract3, // elevator down
    // if no coral, move to stowedEmpty, otherwise move to StowedEE

    // DeAlgae States
    ID_DeAlgaeDeploy1, // start autoalign, elevator & stick up/out, time delay
    ID_DeAlgaeDeployed, // when autoalign good or request removed, stop autoalign & move forward in states
    ID_DeAlgaefy, // move stick up, (maybe) move bot back slightly?
    ID_DeAlgaeRetract1, // elevator down, stick in

    // climb states
    ID_ClimbDeploy1, // elevator up, time delay
    ID_ClimbDeploy2, // arm up(maybe?), intake deploy, time delay
    ID_ClimbDeployed, // elevator down, eject coral, deploy climber, wait for climb signal or removed request
    ID_Climbed, // with climb signal, pull climber down, stay in state unless released back to Deployed
    ID_ClimbRetract1, // elevator up, retract climber, time delay
    ID_ClimbRetract2, // intake in, arm down, time delay
    ID_ClimbRetract3, // elevator down

    // L1 ground states
    ID_L1GroundDeploy1, // elevator up, start autoalign, time delay
    ID_L1GroundDeploy2, // intake out, time delay
    ID_L1GroundDeploy3, // elevator down, wait till autoalign good / score confirmed
    ID_L1GroundScore, // roller out, intake move slightly (maybe?), wait until sensor clear / timeout
    ID_L1GroundRetract1, // roller stop, elevator up, time delay
    ID_L1GroundRetract2, // intake in, time delay
    ID_L1GroundRetract3, // elevator down.
    // if no coral, move to stowedEmpty, if still have coral, move to stowedGround

    // L1 EE States
    ID_L1EEDeploy1, // elevator up, start autoalign, time delay
    ID_L1EEDeploy2, // arm up, time delay
    ID_L1EEDeploy3, // elevator down, wait till autoalign good / score confirmed
    ID_L1EEScore, // run roller, until sensor or timeout
    ID_L1EEWait, // wait until moved back from reef, odom
    ID_L1EERetract1, // elevator up, time delay
    ID_L1EERetract2, // arm down, time delay
    ID_L1EERetract3, // elevator down, time delay
    // if no coral, move to stowedEmpty, if still have coral, move to stowedEE

    // L2 States
    ID_L2Deploy1, // elevator up, start autoalign, time delay
    ID_L2Deploy2, // arm up, time delay
    ID_L2Deploy3, // elevator down, wait till autoalign good / score confirmed
    ID_L2Score, // move arm, until sensor or timeout
    ID_L2Wait, // wait until moved back from reef, odom
    ID_L2Retract1, // elevator up, time delay
    ID_L2Retract2, // arm down, time delay
    ID_L2Retract3, // elevator down, time delay
    // if no coral, move to stowedEmpty, if still have coral, move to stowedEE

    // L3 States
    ID_L3Deploy1, // elevator up, start autoalign, time delay
    ID_L3Deploy2, // arm up, time delay
    ID_L3Deploy3, // elevator down, wait till autoalign good / score confirmed
    ID_L3Score, // move arm, until sensor or timeout
    ID_L3Wait, // wait until moved back from reef, odom
    ID_L3Retract1, // elevator up, time delay
    ID_L3Retract2, // arm down, time delay
    ID_L3Retract3, // elevator down, time delay
    // if no coral, move to stowedEmpty, if still have coral, move to stowedEE

    // L4 States
    ID_L4Deploy1, // elevator up, start autoalign, time delay
    ID_L4Deploy2, // arm up, wait till autoalign good / score confirmed
    ID_L4Score, // move arm, until sensor or timeout
    ID_L4Wait, // wait until moved back from reef, odom
    ID_L4Retract2, // arm down, time delay
    ID_L4Retract3, // elevator down, time delay
    // if no coral, move to stowedEmpty, if still have coral, move to stowedEE

    // Ground -> EE transfer states
    ID_EETransfer1, // elevator up, time delay
    ID_EETransfer2, // intake up, time delay
    ID_EETransfer3, // Run roller, until sensor confirm or timeout
    // if timeout, go to GroundTransfer4, sensor confirm keep moving
    ID_EETransfer4, // stop roller, elevator up, time delay
    ID_EETransfer5, // intake down, time delay
    ID_EETransfer6, // elevator down.
    // confirm with sensors that the coral is still in the EE.
    // move to whichever state makes sense, (stowedEE, stowedGround, stowedEmpty), depending on what the sensors say

    // EE -> Ground transfer states
    ID_GroundTransfer1, // elevator up, time delay
    ID_GroundTransfer2, // intake up, time delay
    ID_GroundTransfer3, // elevator down
    ID_GroundTransfer4, // Run roller, until sensor confirm or timeout
    // if timeout, go to EETransfer3, sensor confirm keep moving
    ID_GroundTransfer5, // stop roller, intake down, time delay
    ID_GroundTransfer6 // elevator down.
    // confirm with sensors that the coral is still in the intake.
    // move to whichever state makes sense, (stowedEE, stowedGround, stowedEmpty), depending on what the sensors say

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



class StowedEmpty : public State {
    STATE_INNER(StowedEmpty)
};

class StowedGround : public State {
    STATE_INNER(StowedGround)
};

class StowedEE : public State {
    STATE_INNER(StowedEE)
};

class GroundDeploy1 : public State {
    STATE_INNER(GroundDeploy1)
};

class GroundDeploy2 : public State {
    STATE_INNER(GroundDeploy2)
};

class GroundDeploy3 : public State {
    STATE_INNER(GroundDeploy3)
};

class GroundDeployed : public State {
    STATE_INNER(GroundDeployed)
};

class GroundRetract1 : public State {
    STATE_INNER(GroundRetract1)
};

class GroundRetract2 : public State {
    STATE_INNER(GroundRetract2)
};

class GroundRetract3 : public State {
    STATE_INNER(GroundRetract3)
};

class StationDeploy1 : public State {
    STATE_INNER(StationDeploy1)
};

class StationDeploy2 : public State {
    STATE_INNER(StationDeploy2)
};

class StationDeploy3 : public State {
    STATE_INNER(StationDeploy3)
};

class StationDeployed : public State {
    STATE_INNER(StationDeployed)
};

class StationWait : public State {
    STATE_INNER(StationWait)
};

class StationRetract1 : public State {
    STATE_INNER(StationRetract1)
};

class StationRetract2 : public State {
    STATE_INNER(StationRetract2)
};

class StationRetract3 : public State {
    STATE_INNER(StationRetract3)
};

class DeAlgaeDeploy1 : public State {
    STATE_INNER(DeAlgaeDeploy1)
};

class DeAlgaeDeployed : public State {
    STATE_INNER(DeAlgaeDeployed)
};

class DeAlgaefy : public State {
    STATE_INNER(DeAlgaefy)
};

class DeAlgaeRetract1 : public State {
    STATE_INNER(DeAlgaeRetract1)
};

class ClimbDeploy1 : public State {
    STATE_INNER(ClimbDeploy1)
};

class ClimbDeploy2 : public State {
    STATE_INNER(ClimbDeploy2)
};

class ClimbDeployed : public State {
    STATE_INNER(ClimbDeployed)
};

class Climbed : public State {
    STATE_INNER(Climbed)
};

class ClimbRetract1 : public State {
    STATE_INNER(ClimbRetract1)
};

class ClimbRetract2 : public State {
    STATE_INNER(ClimbRetract2)
};

class ClimbRetract3 : public State {
    STATE_INNER(ClimbRetract3)
};

class L1GroundDeploy1 : public State {
    STATE_INNER(L1GroundDeploy1)
};

class L1GroundDeploy2 : public State {
    STATE_INNER(L1GroundDeploy2)
};

class L1GroundDeploy3 : public State {
    STATE_INNER(L1GroundDeploy3)
};

class L1GroundScore : public State {
    STATE_INNER(L1GroundScore)
};

class L1GroundRetract1 : public State {
    STATE_INNER(L1GroundRetract1)
};

class L1GroundRetract2 : public State {
    STATE_INNER(L1GroundRetract2)
};

class L1GroundRetract3 : public State {
    STATE_INNER(L1GroundRetract3)
};

class L1EEDeploy1 : public State {
    STATE_INNER(L1EEDeploy1)
};

class L1EEDeploy2 : public State {
    STATE_INNER(L1EEDeploy2)
};

class L1EEDeploy3 : public State {
    STATE_INNER(L1EEDeploy3)
};

class L1EEScore : public State {
    STATE_INNER(L1EEScore)
};

class L1EEWait : public State {
    STATE_INNER(L1EEWait)
};

class L1EERetract1 : public State {
    STATE_INNER(L1EERetract1)
};

class L1EERetract2 : public State {
    STATE_INNER(L1EERetract2)
};

class L1EERetract3 : public State {
    STATE_INNER(L1EERetract3)
};

class L2Deploy1 : public State {
    STATE_INNER(L2Deploy1)
};

class L2Deploy2 : public State {
    STATE_INNER(L2Deploy2)
};

class L2Deploy3 : public State {
    STATE_INNER(L2Deploy3)
};

class L2Score : public State {
    STATE_INNER(L2Score)
};

class L2Wait : public State {
    STATE_INNER(L2Wait)
};

class L2Retract1 : public State {
    STATE_INNER(L2Retract1)
};

class L2Retract2 : public State {
    STATE_INNER(L2Retract2)
};

class L2Retract3 : public State {
    STATE_INNER(L2Retract3)
};

class L3Deploy1 : public State {
    STATE_INNER(L3Deploy1)
};

class L3Deploy2 : public State {
    STATE_INNER(L3Deploy2)
};

class L3Deploy3 : public State {
    STATE_INNER(L3Deploy3)
};

class L3Score : public State {
    STATE_INNER(L3Score)
};

class L3Wait : public State {
    STATE_INNER(L3Wait)
};

class L3Retract1 : public State {
    STATE_INNER(L3Retract1)
};

class L3Retract2 : public State {
    STATE_INNER(L3Retract2)
};

class L3Retract3 : public State {
    STATE_INNER(L3Retract3)
};

class L4Deploy1 : public State {
    STATE_INNER(L4Deploy1)
};

class L4Deploy2 : public State {
    STATE_INNER(L4Deploy2)
};

class L4Score : public State {
    STATE_INNER(L4Score)
};

class L4Wait : public State {
    STATE_INNER(L4Wait)
};

class L4Retract2 : public State {
    STATE_INNER(L4Retract2)
};

class L4Retract3 : public State {
    STATE_INNER(L4Retract3)
};

class EETransfer1 : public State {
    STATE_INNER(EETransfer1)
};

class EETransfer2 : public State {
    STATE_INNER(EETransfer2)
};

class EETransfer3 : public State {
    STATE_INNER(EETransfer3)
};

class EETransfer4 : public State {
    STATE_INNER(EETransfer4)
};

class EETransfer5 : public State {
    STATE_INNER(EETransfer5)
};

class EETransfer6 : public State {
    STATE_INNER(EETransfer6)
};

class GroundTransfer1 : public State {
    STATE_INNER(GroundTransfer1)
};

class GroundTransfer2 : public State {
    STATE_INNER(GroundTransfer2)
};

class GroundTransfer3 : public State {
    STATE_INNER(GroundTransfer3)
};

class GroundTransfer4 : public State {
    STATE_INNER(GroundTransfer4)
};

class GroundTransfer5 : public State {
    STATE_INNER(GroundTransfer5)
};

class GroundTransfer6 : public State {
    STATE_INNER(GroundTransfer6)
};


