#pragma once

#include <Eigen/Core>

#include "Pixel.h"
#include "ITraceable.h"

class Sphere : public ITraceable
{
public:
    Sphere();
    Sphere(const Eigen::Vector3f& position, float radius);

    Pixel Trace(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction);

private:
    Eigen::Vector3f _position;
    float _radius;
};