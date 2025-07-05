import os

enum_values = [
    "StowedEmpty", "StowedGround", "StowedEE",
    "GroundDeploy1", "GroundDeploy2", "GroundDeploy3", "GroundDeployed",
    "GroundRetract1", "GroundRetract2", "GroundRetract3",
    "StationDeploy1", "StationDeploy2", "StationDeploy3", "StationDeployed", "StationWait",
    "StationRetract1", "StationRetract2", "StationRetract3",
    "DeAlgaeDeploy1", "DeAlgaeDeployed", "DeAlgaefy", "DeAlgaeRetract1",
    "ClimbDeploy1", "ClimbDeploy2", "ClimbDeployed", "Climbed",
    "ClimbRetract1", "ClimbRetract2", "ClimbRetract3",
    "L1GroundDeploy1", "L1GroundDeploy2", "L1GroundDeploy3", "L1GroundScore",
    "L1GroundRetract1", "L1GroundRetract2", "L1GroundRetract3",
    "L1EEDeploy1", "L1EEDeploy2", "L1EEDeploy3", "L1EEScore", "L1EEWait",
    "L1EERetract1", "L1EERetract2", "L1EEREtract3",
    "L2Deploy1", "L2Deploy2", "L2Deploy3", "L2Score", "L2Wait",
    "L2Retract1", "L2Retract2", "L2REtract3",
    "L3Deploy1", "L3Deploy2", "L3Deploy3", "L3Score", "L3Wait",
    "L3Retract1", "L3Retract2", "L3REtract3",
    "L4Deploy1", "L4Deploy2", "L4Score", "L4Wait",
    "L4Retract2", "L4REtract3",
    "EETransfer1", "EETransfer2", "EETransfer3", "EETransfer4", "EETransfer5", "EETransfer6",
    "GroundTransfer1", "GroundTransfer2", "GroundTransfer3", "GroundTransfer4", "GroundTransfer5", "GroundTransfer6"
]

os.makedirs("output_cpp", exist_ok=True)

for i, name in enumerate(enum_values):
    filename = f"output_cpp/{i:02d}-{name}.cpp"
    content = f"""#include "States.h"

void {name}::initialize_impl() {{}}

State* {name}::loop_impl() {{
    return nullptr;
}};
"""
    with open(filename, "w") as f:
        f.write(content)

print("\u2705 Files generated in the 'output_cpp' directory.")
