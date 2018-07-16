#include "Direction.h"

Direction::Direction(float x, float y, float z)
    : _normalizedDirection(Eigen::Vector3f{x, y, z}.normalized())
{
}

float Direction::X() const
{
    return _normalizedDirection.x();
}

float Direction::Y() const
{
    return _normalizedDirection.y();
}

float Direction::Z() const
{
    return _normalizedDirection.z();
}