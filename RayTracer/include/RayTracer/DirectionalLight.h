#pragma once

#include "ILight.h"

#include <Eigen/Core>

class DirectionalLight : public ILight
{
public:
    DirectionalLight(const Eigen::Vector3f& direction, float intensity, const Eigen::Vector3f& color);

    Eigen::Vector3f GetToLightDirection(const Eigen::Vector3f& hitPoint) const;

private:
    Eigen::Vector3f _direction;
};