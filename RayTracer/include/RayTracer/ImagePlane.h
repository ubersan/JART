#pragma once

#include <vector>

#include "Pixel.h"

class ImagePlane
{
public:
    ImagePlane(int columns, int rows, const Eigen::Vector3f& position);

    std::vector<unsigned char> GetPixelsInRGBAFormat() const;

    int Columns() const;
    int Rows() const;

    void SetPixel(int row, int column, const Pixel& pixel);

private:
    unsigned char* GetDataPointer() const;

    int _columns;
    int _rows;

    Eigen::Vector3f _position;

    std::vector<Pixel> _pixels;
};