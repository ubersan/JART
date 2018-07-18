#include "Sphere.h"
#include <limits>

using namespace std;
using namespace Eigen;

Sphere::Sphere(const Vector3f& center, float radius)
    : _radius(radius), _radius2(radius*radius), _center(center)
{
}

tuple<bool, float> Sphere::Intersect(const Vector3f& origin, const Vector3f& direction) const
{    
    auto L = _center - origin;
    auto tca = L.dot(direction);
    if (tca < 0)
    {
        return make_tuple(false, 0.f);
    }

    auto d2 = L.dot(L) - tca * tca;
    if (d2 > _radius2)
    {
        return make_tuple(false, 0.f);
    }

    auto thc = sqrtf(_radius2 - d2);
    auto t0 = tca - thc;
    auto t1 = tca + thc;
    if (t0 < 0)
    {
        // if t0 is negative, let's use t1 instead
        t0 = t1;
        if (t0 < 0)
        {
            // both t0 and t1 are negative
            return make_tuple(false, 0.f);
        }
    }
    
    return make_tuple(true, t0);
}

Eigen::Vector3f Sphere::GetNormalAt(const Eigen::Vector3f& hitPoint) const
{
    return (hitPoint - _center).normalized();
}