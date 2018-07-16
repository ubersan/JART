#include "Pixel.h"

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b)
    : _rgba(RGBA{r, g, b, 255})
{
}

Pixel Pixel::Black()
{
    return Pixel(0, 0, 0);
}

Pixel Pixel::Red()
{
    return Pixel(255, 0, 0);
}

bool Pixel::operator==(const Pixel& other) const
{
    return _rgba == other._rgba;
}