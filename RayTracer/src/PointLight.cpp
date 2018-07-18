#include "PointLight.h"

using namespace std;
using namespace Eigen;

PointLight::PointLight(const Vector3f& center, float intensity, const Vector3f& color)
    : ILight(center, intensity, color)
{
}

Vector3f PointLight::GetToLightDirection(const Vector3f& hitPoint) const
{
    return (center - hitPoint).normalized();
}

Vector3f PointLight::GetContributionAccordingToDistance(const Vector3f& hitPoint) const
{
    auto distance2 = (hitPoint - center).squaredNorm();

    return intensity * color / (4.f * M_PI * distance2);   
}