#include "Plane.h"

using namespace std;
using namespace Eigen;

Plane::Plane(const Vector3f& pointOnPlane, const Vector3f& normal, Material material)
    : IIntersectable(material), _pointOnPlane(pointOnPlane), _normal(normal)
{
}

tuple<bool, float> Plane::Intersect(const Vector3f& origin, const Vector3f& direction) const
{
    auto denominator = _normal.dot(direction);

    if (abs(denominator) > 1e-14)
    {
        auto t = (_pointOnPlane - origin).dot(_normal) / denominator;

        return make_tuple(t >= 0.f, t);
    }

    return make_tuple(false, 0.f);
}

Vector3f Plane::GetNormalAt(const Vector3f& hitPoint) const
{
    return _normal;
}