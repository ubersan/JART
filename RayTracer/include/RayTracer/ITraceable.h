#pragma once

#include <Eigen/Core>
#include "Pixel.h"

class ITraceable
{
public:
    virtual Pixel Trace(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction)
    {
        throw std::runtime_error("Not implemented");
    }
};