#pragma once

#include "IIntersectable.h"

#include <Eigen/Core>
#include <tuple>

class PointLight : public IIntersectable
{
public:
    PointLight(const Eigen::Vector3f& position);

    std::tuple<bool, float> Intersect(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction) const;
    Eigen::Vector3f GetNormalAt(const Eigen::Vector3f& hitPoint) const;
private:
    Eigen::Vector3f _position;
};