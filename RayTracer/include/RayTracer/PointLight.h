#pragma once

#include "ILight.h"

#include <Eigen/Core>
#include <tuple>

class PointLight : public ILight
{
public:
    PointLight(const Eigen::Vector3f& center, float intensity, const Eigen::Vector3f& color);

    Eigen::Vector3f GetToLightDirection(const Eigen::Vector3f& hitPoint) const;
    Eigen::Vector3f GetContributionAccordingToDistance(const Eigen::Vector3f& hitPoint) const;
};