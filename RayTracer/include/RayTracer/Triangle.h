#pragma once

#include "IIntersectable.h"

#include <tuple>
#include <Eigen/Core>

class Triangle : public IIntersectable
{
public:
    // Assumes that vertices are given in counter clockwise order, such that the normal is oriented correctly.
    Triangle(const Eigen::Vector3f& a, const Eigen::Vector3f& b, const Eigen::Vector3f& c, Material material);

    std::tuple<bool, float> Intersect(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction) const;
    Eigen::Vector3f GetNormalAt(const Eigen::Vector3f& hitPoint) const;

private:
    Eigen::Vector3f _a;
    Eigen::Vector3f _b;
    Eigen::Vector3f _c;

    Eigen::Vector3f _normal;
};