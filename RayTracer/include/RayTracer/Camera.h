#pragma once

#include <Eigen/Core>

class Camera
{
public:
    Camera();
    
    const Eigen::Vector3f& GetPosition() const;

private:
    Eigen::Vector3f _position;
    Eigen::Vector3f _lookAt;
    Eigen::Vector3f _up;
};