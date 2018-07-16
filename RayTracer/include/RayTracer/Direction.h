#pragma once

#include <Eigen/Core>

class Direction
{
public:
    Direction(float x, float y, float z);

    float X() const;
    float Y() const;
    float Z() const;
private:
    Eigen::Vector3f _normalizedDirection;
};