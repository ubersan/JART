#include "Sphere.h"
#include <limits>

Sphere::Sphere(const Eigen::Vector3f& center, float radius)
    : _radius(radius), _radius2(radius*radius), _center(center)
{
}

std::tuple<bool, float> Sphere::Intersect(const Eigen::Vector3f &orig, const Eigen::Vector3f &dir) const
{
    const float kInfinity = std::numeric_limits<float>::max();
    float t0, t1; // solutions for t if the ray intersects
    float t = kInfinity;
    // geometric solution
    auto L = _center - orig;
    float tca = L.dot(dir);
    if (tca < 0) return std::make_tuple(false, t);
    float d2 = L.dot(L) - tca * tca;
    if (d2 > _radius2) return std::make_tuple(false, t);
    float thc = sqrt(_radius2 - d2);
    t0 = tca - thc;
    t1 = tca + thc;

    if (t0 < 0) {
        t0 = t1; // if t0 is negative, let's use t1 instead
        if (t0 < 0) return std::make_tuple(false, t); // both t0 and t1 are negative
    }
    t = t0;
    return std::make_tuple(true, t);
}