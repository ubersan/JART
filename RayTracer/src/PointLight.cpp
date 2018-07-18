#include "PointLight.h"

using namespace std;
using namespace Eigen;

PointLight::PointLight(const Vector3f& position)
    : _position(position)
{
}

tuple<bool, float> PointLight::Intersect(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction) const
{
    // a point light is never intersected
    return make_tuple(false, 0.f);
}

Eigen::Vector3f PointLight::GetNormalAt(const Eigen::Vector3f& hitPoint) const
{
    // we never will/can intersect this light
    return Vector3f::Zero();
}