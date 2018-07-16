#pragma once

#include <vector>

#include "Pixel.h"
#include "Position.h"

class ImagePlane
{
public:
    ImagePlane(int columns, int rows, const Position& position);
    ImagePlane(int columns, int rows, const std::vector<unsigned char> imageData);

    std::vector<unsigned char> GetPixelsInRGBAFormat() const;

    int Columns() const;
    int Rows() const;

    void SetPixel(int row, int column, const Pixel& pixel);
    Pixel GetPixel(int row, int column) const;

private:
    unsigned char* GetDataPointer() const;

    int _columns;
    int _rows;

    Position _position;

    std::vector<Pixel> _pixels;
};