#include "DirectionalLight.h"

#include <limits>

using namespace std;
using namespace Eigen;

DirectionalLight::DirectionalLight(const Vector3f& direction, float intensity, const Vector3f& color)
    : ILight(Vector3f::Zero(), intensity, color), _direction(direction)
{
}

Vector3f DirectionalLight::GetToLightDirection(const Vector3f& hitPoint) const
{
    return -_direction;
}

Vector3f DirectionalLight::GetContributionAccordingToDistance(const Vector3f& hitPoint) const
{
    // The directional light is placed at infinity. Thus there is no falloff and the contribution is constant.
    return intensity * color;
}

float DirectionalLight::GetMaximalHitDistance(const Eigen::Vector3f& hitPoint) const
{
    // All hits when shadow tracing are viable.
    return numeric_limits<float>::max();
}