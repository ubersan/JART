#include "Position.h"
#include <Eigen/Core>

Position::Position(float x, float y, float z)
    : _position{x, y, z}
{
}

Position::Position(const Eigen::Vector3f& position)
    : _position{position}
{
}

float Position::X() const
{
    return _position.x();
}

float Position::Y() const
{
    return _position.y();
}

float Position::Z() const
{
    return _position.z();
}

float Position::Dot(const Position& other)
{
    return _position.dot(other._position);
}

float Position::Dot(const Direction& direction)
{
    return _position.dot(Eigen::Vector3f{direction.X(), direction.Y(), direction.Z()});
}

Position Position::operator+(const Position& other)
{
    return Position{_position + other._position};
}

Position Position::operator-(const Position& other) const
{
    return Position{_position - other._position};
}