#include "Sphere.h"

Sphere::Sphere()
    : Sphere(Position{0.f, 0.f, 0.f}, 1.f)
{
}

Sphere::Sphere(const Position& center, float radius)
    : _center(center), _radius(radius)
{
}

bool Sphere::Trace(const Position& origin, const Direction& direction) const
{    
    auto L = _center - origin;
    auto tca = L.Dot(direction);
    auto d2 = L.Dot(L) - tca*tca;
    if (d2 > _radius*_radius)
    {
        return false;
    }

    auto thc = sqrtf(_radius*_radius - d2);
    auto t0 = tca - thc;
    auto t1 = tca + thc;

    if (t0 > t1)
    {
        std::swap(t0, t1);
    }

    if (t0 < t1)
    {
        t0 = t1;
        if (t0 < 0)
        {
            return false;
        }
    }
    
    return true;
}