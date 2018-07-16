#include "Camera.h"

Camera::Camera()
    : _position(Eigen::Vector3f{0.f, 0.f, 10.f}), _lookAt(Eigen::Vector3f{0.f, 0.f, -1.f}), _up(Eigen::Vector3f{0.f, 1.f, 0.f})
{
}

const Eigen::Vector3f& Camera::GetPosition() const
{
    return _position;
}