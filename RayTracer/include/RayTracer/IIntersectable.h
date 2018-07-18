#pragma once

#include "Material.h"

#include <tuple>
#include <Eigen/Core>

class IIntersectable
{
public:
    IIntersectable(Material material)
        : material(material)
    {
    }
    
    virtual ~IIntersectable() {}
    
    virtual std::tuple<bool, float> Intersect(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction) const = 0;
    virtual Eigen::Vector3f GetNormalAt(const Eigen::Vector3f& hitPoint) const = 0;

    Material material;
};