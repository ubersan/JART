#pragma once

#include <Eigen/Core>
#include "Pixel.h"

class ITraceable
{
public:
    // If this is a pure virtual method, then we can't instantiate a vector of
    // ITraceables, thus throw. Another possibility is to have a vector of
    // ITraceable*, but then we lose the very important instance locality when
    // iterating over the objects. This can happens a lot, because every ray checks
    // all objects for collisions, shadowing, ect...
    virtual bool Trace(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction) const
    {
        throw std::runtime_error("Not implemented");
    }
};