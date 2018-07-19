#include "Plane.h"
#include <iostream>

#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

Plane::Plane(const Vector3f& pointOnPlane, const Vector3f& normal, Material material)
    : IIntersectable(material), _pointOnPlane(pointOnPlane), _normal(normal), _isRectangle(false)
{
}

Plane::Plane(const Vector3f& center, const Vector3f& normal, const Vector3f& widthDirection, float totalWidth, float totalHeight, Material material)
    : IIntersectable(material), _pointOnPlane(center), _normal(normal), _widthDirection(widthDirection), _halfWidth(totalWidth / 2.f), _halfHeight(totalHeight / 2.f), _isRectangle(true)
{
    _heightDirection = _normal.cross(_widthDirection);
}

tuple<bool, float> Plane::Intersect(const Vector3f& origin, const Vector3f& direction) const
{
    auto denominator = _normal.dot(direction);

    if (abs(denominator) > 1e-14)
    {
        auto t = (_pointOnPlane - origin).dot(_normal) / denominator;

        if (t >= 0.f && _isRectangle)
        {
            auto hitPoint = origin + t*direction;
            auto centerOffset = hitPoint - _pointOnPlane;
            
            auto isInWideRange = abs(centerOffset.dot(_widthDirection)) <= _halfWidth;
            auto isInHeightRange = abs(centerOffset.dot(_heightDirection)) <= _halfHeight;

            return make_tuple(isInWideRange && isInHeightRange, t);
        }

        return make_tuple(t >= 0.f, t);
    }

    return make_tuple(false, 0.f);
}

Vector3f Plane::GetNormalAt(const Vector3f& hitPoint) const
{
    return _normal;
}