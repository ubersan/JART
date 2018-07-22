#include "Triangle.h"

#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

Triangle::Triangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, Material material)
    : IIntersectable(material), _a(a), _b(b), _c(c)
{
    _normal = (_b - a).normalized().cross((_c - _a).normalized()).normalized();
}

tuple<bool, float> Triangle::Intersect(const Vector3f& origin, const Vector3f& direction) const
{
    // see https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
    auto e1 = _b - _a;
    auto e2 = _c - _a;
    auto h = direction.cross(e2);
    auto a = e1.dot(h);
    if (a > -1e-4 && a < 1e-4)
    {
        return make_tuple(false, 0.f);
    }

    auto f = 1/a;
    auto s = origin - _a;
    auto u = f * s.dot(h);
    if (u < 0.f || u > 1.f)
    {
        return make_tuple(false, 0.f);
    }

    auto q = s.cross(e1);
    auto v = f * direction.dot(q);
    if (v < 0.f || u + v > 1.f)
    {
        return make_tuple(false, 0.f);
    }

    auto t = f * e2.dot(q);
    if (t > 1e-4)
    {
        return make_tuple(true, t);
    }

    return make_tuple(false, 0.f);
}

Vector3f Triangle::GetNormalAt(const Vector3f& hitPoint) const
{
    return _normal;
}