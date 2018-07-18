#include "PointLight.h"

using namespace std;
using namespace Eigen;

PointLight::PointLight(const Vector3f& center, float intensity, const Vector3f& color)
    : ILight(center, intensity, color)
{
}

Eigen::Vector3f PointLight::GetToLightDirection(const Eigen::Vector3f& hitPoint) const
{
    return (center - hitPoint).normalized();
}