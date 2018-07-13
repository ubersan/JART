#include "Sphere.h"

Sphere::Sphere()
{
}

Sphere::Sphere(const Eigen::Vector3f& position, float radius)
    : _position(position), _radius(radius)
{
}

Pixel Sphere::Trace(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction)
{
    return Pixel(0, 0, 0);
}