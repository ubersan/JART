#pragma once

#include <Eigen/Core>

class Direction
{
public:
    Direction(float x, float y, float z);
    Direction(const Eigen::Vector3f& notNormalizedDirection);

    Eigen::Vector3f GetDirection() const;
private:
    Eigen::Vector3f _normalizedDirection;
};