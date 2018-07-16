#pragma once

#include <Eigen/Core>
#include "Direction.h"

class Position
{
public:
    Position(float x, float y, float z);
    Position(const Eigen::Vector3f& position);

    float X() const;
    float Y() const;
    float Z() const;

    float Dot(const Position& other);
    float Dot(const Direction& direction);

    Position operator+(const Position& other);
    Position operator-(const Position& other) const;
private:
    Eigen::Vector3f _position;
};