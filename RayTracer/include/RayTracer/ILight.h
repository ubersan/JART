#pragma once

#include <limits>
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
    virtual Eigen::Vector3f GetContributionAccordingToDistance(const Eigen::Vector3f& hitPoint) const = 0;

    // When shadow tracing a point light, hits with distance greater than the distance to the shaded object have to be ignored.
    virtual float GetMaximalHitDistance(const Eigen::Vector3f& hitPoint) const = 0;
};