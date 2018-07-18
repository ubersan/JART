#pragma once

#include "IIntersectable.h"
#include "Material.h"

#include <tuple>
#include <Eigen/Core>

class Sphere : public IIntersectable
{
public:
    Sphere(const Eigen::Vector3f& center, float radius, Material material);

    std::tuple<bool, float> Intersect(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction) const;
    Eigen::Vector3f GetNormalAt(const Eigen::Vector3f& hitPoint) const;

private:
    float _radius2;
    Eigen::Vector3f _center;
};