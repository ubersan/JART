#include "Sphere.h"

Sphere::Sphere()
{
}

Sphere::Sphere(const Eigen::Vector3f& position, float radius)
    : _position(position), _radius(radius)
{
}