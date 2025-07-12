#pragma once

#include <Arduino.h>
#include <vector>
#include <cmath>
#include <limits>

#include "Util.h"
#include "Transforms.h"

class GeoHelper {
public:
    // Euclidean distance between 2D points
    static double distance(const Pose2D& a, const Pose2D& b) {
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    // Normalize angle to [0, 360)
    static double normalizeAngle(double angle) {
        while (angle < 0) angle += 360;
        while (angle >= 360) angle -= 360;
        return angle;
    }

    // Return smallest angular difference [0, 180]
    static double angleDifference(double a, double b) {
        double diff = std::fabs(normalizeAngle(a) - normalizeAngle(b));
        return (diff > 180.0) ? 360.0 - diff : diff;
    }

    // Find index of closest point; optionally determine if heading is closer to 180°
    static int findClosestPointIndex(const Pose2D& target,
                                     const std::vector<Pose2D>& points,
                                     bool* isOppositeHeading = nullptr) {
        double minDist = std::numeric_limits<double>::max();
        int closestIndex = -1;

        for (size_t i = 0; i < points.size(); ++i) {
            double dist = distance(target, points[i]);
            if (dist < minDist) {
                minDist = dist;
                closestIndex = static_cast<int>(i);
            }
        }

        if (isOppositeHeading && closestIndex != -1) {
            double diff = angleDifference(target.theta, points[closestIndex].theta);
            *isOppositeHeading = (diff > 90.0); // More opposite than aligned
        }

        return closestIndex;
    }

    // Ray-casting algorithm for point-in-polygon
    static bool isPointInsidePolygon(const Pose2D& point, const std::vector<Pose2D>& polygon) {
        int n = polygon.size();
        if (n < 3) return false;

        bool inside = false;
        for (int i = 0, j = n - 1; i < n; j = i++) {
            const Pose2D& pi = polygon[i];
            const Pose2D& pj = polygon[j];

            bool intersect = ((pi.y > point.y) != (pj.y > point.y)) &&
                             (point.x < (pj.x - pi.x) * (point.y - pi.y) /
                                ((pj.y - pi.y) + 1e-10) + pi.x);
            if (intersect) inside = !inside;
        }
        return inside;
    }

    // Decide whether robot should approach the target inline or opposite to minimize heading change
    static bool shouldApproachInline(const Pose2D& robot, const Pose2D& target) {
        double inlineDiff = angleDifference(robot.theta, target.theta);
        double oppositeDiff = angleDifference(robot.theta, normalizeAngle(target.theta + 180));
        return inlineDiff <= oppositeDiff;
    }

    // Return the best approach heading (either target.theta or target.theta + 180)
    static double getBestApproachHeading(const Pose2D& robot, const Pose2D& target) {
        return shouldApproachInline(robot, target)
               ? normalizeAngle(target.theta)
               : normalizeAngle(target.theta + 180);
    }

    // Return a full Pose2D with x, y from target and best heading to approach it
    static Pose2D getBestApproachPose(const Pose2D& robot, const Pose2D& target) {
        Pose2D result = target;
        result.theta = getBestApproachHeading(robot, target);
        return result;
    }
};

