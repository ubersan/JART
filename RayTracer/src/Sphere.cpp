#include "Sphere.h"

Sphere::Sphere()
    : Sphere(Eigen::Vector3f{0.f, 0.f, 0.f}, 1.f)
{
}

Sphere::Sphere(const Eigen::Vector3f& position, float radius)
    : _position(position), _radius(radius)
{
}

bool Sphere::Trace(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction) const
{    
    auto L = _position - origin;
    auto tca = L.dot(direction);
    auto d2 = L.dot(L) - tca*tca;
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

    auto t = t0;

    return true;
}