#include "Camera.h"

Camera::Camera(const Position& position, const Direction& lookAt, const Direction& up)
    : _position(position), _lookAt(lookAt), _up(up)
{
}

Position Camera::GetPosition() const
{
    return _position;
}