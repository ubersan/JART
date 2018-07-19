#pragma once

#include "IIntersectable.h"
#include "Material.h"

#include <tuple>
#include <Eigen/Core>

class Plane : public IIntersectable
{
public:
    Plane(const Eigen::Vector3f& pointOnPlane, const Eigen::Vector3f& normal, Material material);
    Plane(const Eigen::Vector3f& center, const Eigen::Vector3f& normal, const Eigen::Vector3f& widthDirection, float totalWidth, float totalHeight, Material material);

    std::tuple<bool, float> Intersect(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction) const;
    Eigen::Vector3f GetNormalAt(const Eigen::Vector3f& hitPoint) const;

private:
    Eigen::Vector3f _pointOnPlane;
    Eigen::Vector3f _normal;
    Eigen::Vector3f _widthDirection;
    Eigen::Vector3f _heightDirection;

    // Only store half the given total width, such that the 'is-inside' check is easier. Max-width from center
    // along the width and height direction is _halfWidth, resp. _halfHeight.
    float _halfWidth;
    float _halfHeight;
    bool _isRectangle;
};