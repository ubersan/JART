#pragma once

#include "Position.h"
#include "Pixel.h"
#include "ITraceable.h"

class Sphere : public ITraceable
{
public:
    Sphere();
    Sphere(const Position& center, float radius);

    bool Trace(const Position& origin, const Direction& direction) const;

private:
    Position _center;
    float _radius;
};