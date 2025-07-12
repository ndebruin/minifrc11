#pragma once

#include <Arduino.h>
#include <vector>

#include "Util.h"

Pose2D applyTransforms(Pose2D inputPose, Goal goal){
    
}

const Pose2D robotToSensorTransform = {-7.0, -7.5, 180.0};
const Pose2D armL1ForwardToRobotTransform = {-21.154546, 101.663660, 0.0};
const Pose2D armL2ForwardToRobotTransform = {-21.154546, 103.558785, 0.0};
const Pose2D armL3ForwardToRobotTransform = {-21.154546, 61.899621, 0.0};
const Pose2D armL1BackwardToRobotTransform = {-21.154546, -101.663660, 0.0};
const Pose2D armL2BackwardToRobotTransform = {-21.154546, -103.558785, 0.0};
const Pose2D armL3BackwardToRobotTransform = {-21.154546, -61.899621, 0.0};
const Pose2D groundL1ToRobotTransform = {-86.310305, 0.0, 90.0};
const Pose2D armForwardStationToRobotTransform = {-21.154546, 61.899621, 0.0};
const Pose2D armBackwardStationToRobotTransform = {-21.154546, -61.899621, 0.0};

// this places the 0,0,0 origin in the corner of the left coral station where the driver station wall and the left field wall intercet from the driver stations' perspective.
// with heading being along the left field wall

// all coords in mm,mm,deg

// we will be running with this for both sides, as Reefscape is a rotationally symmetric field

// reef faces. starting from face closest to driver station wall, CCW+
const Pose2D ReefFaceA = {887.4125, 812.80, 0.0};
const Pose2D ReefFaceB = {1044.575, 903.5378115, 60.0};
const Pose2D ReefFaceC = {1044.575, 1085.013435, 120.0};
const Pose2D ReefFaceD = {887.4125, -1175.751247, 180.0};
const Pose2D ReefFaceE = {730.25, 1085.013435, 240.0};
const Pose2D ReefFaceF = {730.25, 903.5378115, 300.0};

// reef branches (as offsets from faces)
const Pose2D ReefBranchALeft  = {ReefFaceA.x - 33.655000, ReefFaceA.y + 11.836403, ReefFaceA.theta};
const Pose2D ReefBranchARight = {ReefFaceA.x + 33.655000, ReefFaceA.y + 11.836403, ReefFaceA.theta};

const Pose2D ReefBranchBLeft  = {ReefFaceB.x + -27.078, ReefFaceB.y + -23.227884, ReefFaceB.theta};
const Pose2D ReefBranchBRight = {ReefFaceB.x + 6.576875, ReefFaceB.y + 35.064286, ReefFaceB.theta};

const Pose2D ReefBranchCLeft  = {ReefFaceC.x + 6.576875, ReefFaceC.y + -35.064286, ReefFaceC.theta};
const Pose2D ReefBranchCRight = {ReefFaceC.x + -27.078, ReefFaceC.y + 23.227884, ReefFaceC.theta};

const Pose2D ReefBranchDLeft  = {ReefFaceD.x - 33.655000, ReefFaceD.y + -11.836403, ReefFaceD.theta};
const Pose2D ReefBranchDRight = {ReefFaceD.x + 33.655000, ReefFaceD.y + -11.836403, ReefFaceD.theta};

const Pose2D ReefBranchELeft  = {ReefFaceE.x + 27.078, ReefFaceE.y + 23.227884, ReefFaceE.theta};
const Pose2D ReefBranchERight = {ReefFaceE.x + -6.576875, ReefFaceE.y + -35.064286, ReefFaceE.theta};

const Pose2D ReefBranchFLeft  = {ReefFaceF.x + -6.576875, ReefFaceF.y + 35.064286, ReefFaceF.theta};
const Pose2D ReefBranchFRight = {ReefFaceF.x + 27.078, ReefFaceF.y + -23.227884, ReefFaceF.theta};

// Reef Region as a hexagon around the reef
const std::vector<Pose2D> ReefRegion = {
    {743.531642, 745.067, 0},
    {1031.293358, 745.067, 0},
    {1175.174216, 994.275623, 0},
    {1031.293358, 1243.484580, 0},
    {743.531642, 1243.484580, 0},
    {599.650784, 994.275623, 0}
};

// coral stations
const Pose2D CoralStationLeft = {151.895366, 212.053307, 126.0};
const Pose2D CoralStationRight = {1624.413398, 212.053307, 234.0};

// coral station areas
const std::vector<Pose2D> CoralStationRegionLeft = {
    {299.474213, 8.846420, 0},
    {299.474213, 30, 0},
    {0.430293, 430, 0},
    {0.430293, 412.557795, 0}
};

const std::vector<Pose2D> CoralStationRegionRight = {
    {1476.834550, 8.846420, 0},
    {1476.834550, 30, 0},
    {1775.136589, 430, 0},
    {1775.136589, 413.106087, 0}
};

const std::vector<Pose2D> AllLeftBranches = {
    ReefBranchALeft,
    ReefBranchBLeft,
    ReefBranchCLeft,
    ReefBranchDLeft,
    ReefBranchELeft,
    ReefBranchFLeft
};

enum LeftReefBranchID {
    ReefBranchA_Left,
    ReefBranchB_Left,
    ReefBranchC_Left,
    ReefBranchD_Left,
    ReefBranchE_Left,
    ReefBranchF_Left
};

Pose2D getLeftReefBranch(LeftReefBranchID id){
    return AllLeftBranches.at(id);
};

const std::vector<Pose2D> AllRightBranches = {
    ReefBranchARight,
    ReefBranchBRight,
    ReefBranchCRight,
    ReefBranchDRight,
    ReefBranchERight,
    ReefBranchFRight
};

enum RightReefBranchID {
    ReefBranchA_Right,
    ReefBranchB_Right,
    ReefBranchC_Right,
    ReefBranchD_Right,
    ReefBranchE_Right,
    ReefBranchF_Right
};

Pose2D getRightReefBranch(RightReefBranchID id){
    return AllRightBranches.at(id);
};



const std::vector<Pose2D> AllFaces = {
    ReefFaceA, ReefFaceB, ReefFaceC,
    ReefFaceD, ReefFaceE, ReefFaceF
};

enum ReefFaceID {
    ReefFace_A,
    ReefFace_B,
    ReefFace_C,
    ReefFace_D,
    ReefFace_E,
    ReefFace_F
};

Pose2D getReefFace(ReefFaceID id){
    return AllFaces.at(id);
}

const std::vector<Pose2D> AllCoralStations = {
    CoralStationLeft, CoralStationRight
};
