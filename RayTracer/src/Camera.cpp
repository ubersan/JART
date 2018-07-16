#include "Camera.h"

Camera::Camera(const Position& position, const Direction& lookAt, const Direction& up)
    : _position(position), _lookAt(lookAt), _up(up), _imagePlane(ImagePlane{900, 600, position + lookAt})
{
    // The ImagePlane is 1 unit away from the camera
    // With a FOV of 45 degrees this yields an imagePlane height
    // of 2 units and a corresponding width according to the pixel
    // ratio between widht and height
    _pixelSize = 2.f / _imagePlane.Rows();
}

Position Camera::GetPosition() const
{
    return _position;
}

float Camera::GetPixelSize() const
{
    return _pixelSize;
}

int Camera::Rows() const
{
    return _imagePlane.Rows();
}

int Camera::Columns() const
{
    return _imagePlane.Columns();
}

void Camera::SetPixel(int row, int column, const Pixel& pixel)
{
    _imagePlane.SetPixel(row, column, pixel);
}

Position Camera::GetTopLeftPixelPosition() const
{
    auto topLeftCenterX = -_pixelSize * _imagePlane.Rows() / 2 + (_pixelSize / 2.f);
    auto topLeftCenterY = _pixelSize * _imagePlane.Columns() / 2 - (_pixelSize / 2.f); 

    return Position{topLeftCenterX, topLeftCenterY, _position.Z()} + _lookAt;
}

ImagePlane Camera::GetImagePlane() const
{
    return _imagePlane;
}