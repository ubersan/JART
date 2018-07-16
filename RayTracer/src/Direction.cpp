#include "Direction.h"

Direction::Direction(float x, float y, float z)
    : Direction(Eigen::Vector3f{x, y, z})
{
}

Direction::Direction(const Eigen::Vector3f& notNormalizedDirection)
    : _normalizedDirection(notNormalizedDirection.normalized())
{
}

Eigen::Vector3f Direction::GetDirection() const
{
    return _normalizedDirection;
}