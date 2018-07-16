#pragma once

#include <Eigen/Core>

#include "Direction.h"
#include "Position.h"

class Camera
{
public:
    Camera(const Position& position, const Direction& lookAt, const Direction& up);
    
    Position GetPosition() const;

private:
    Position _position;
    Direction _lookAt;
    Direction _up;
};