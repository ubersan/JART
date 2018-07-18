#include "DirectionalLight.h"

using namespace Eigen;

DirectionalLight::DirectionalLight(const Vector3f& direction, float intensity, const Vector3f& color)
    : ILight(Vector3f::Zero(), intensity, color), _direction(direction)
{
}

Vector3f DirectionalLight::GetToLightDirection(const Vector3f& hitPoint) const
{
    return -_direction;
}