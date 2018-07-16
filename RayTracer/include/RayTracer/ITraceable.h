#pragma once

#include "Position.h"
#include "Direction.h"
#include "Pixel.h"

class ITraceable
{
public:
    virtual bool Trace(const Position& origin, const Direction& direction) const
    {
        throw std::runtime_error("Not implemented");
    }

    virtual ~ITraceable() {}
};