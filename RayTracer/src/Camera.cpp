#include "Camera.h"

Camera::Camera()
    : _position(Eigen::Vector3f::Zero()), _lookAt(Eigen::Vector3f{0.f, 0.f, -1.f}), _up(Eigen::Vector3f{0.f, 1.f, 0.f})
{
}