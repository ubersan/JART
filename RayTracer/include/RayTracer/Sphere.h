#pragma once

#include <Eigen/Core>

class Sphere
{
public:
    Sphere();
    Sphere(const Eigen::Vector3f& position, float radius);

private:
    Eigen::Vector3f _position;
    float _radius;
};