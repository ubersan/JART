#pragma once

#include <Eigen/Core>

#include "Direction.h"
#include "Position.h"
#include "ImagePlane.h"

class Camera
{
public:
    Camera(const Position& position, const Direction& lookAt, const Direction& up);
    
    Position GetPosition() const;
    float GetPixelSize() const;
    Position GetTopLeftPixelPosition() const;

    int Rows() const;
    int Columns() const;

    void SetPixel(int row, int column, const Pixel& pixel);

    ImagePlane GetImagePlane() const;

private:
    Position _position;
    Direction _lookAt;
    Direction _up;

    ImagePlane _imagePlane;

    float _pixelSize;
};