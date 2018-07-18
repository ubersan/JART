#pragma once

#include <Eigen/Core>

class ILight
{
public:
    ILight(const Eigen::Vector3f& center, float intensity, const Eigen::Vector3f& color)
        : center(center), intensity(intensity), color(color)
    {
    }

    ~ILight() {}

    Eigen::Vector3f center;

    float intensity;
    Eigen::Vector3f color;

    // This returns the direction from the hitpoint TO the light.
    virtual Eigen::Vector3f GetToLightDirection(const Eigen::Vector3f& hitPoint) const = 0;
};