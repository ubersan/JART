#pragma once

#include "IIntersectable.h"
#include "Material.h"

#include <tuple>
#include <Eigen/Core>

class Plane : public IIntersectable
{
public:
    Plane(const Eigen::Vector3f& pointOnPlane, const Eigen::Vector3f& normal, Material material);

    std::tuple<bool, float> Intersect(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction) const;
    Eigen::Vector3f GetNormalAt(const Eigen::Vector3f& hitPoint) const;

private:
    Eigen::Vector3f _pointOnPlane;
    Eigen::Vector3f _normal;
};