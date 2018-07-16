#pragma once

#include <Eigen/Core>

using RGBA = Eigen::Matrix<unsigned char, 4, 1>;

class Pixel
{
public:
    Pixel(unsigned char r, unsigned char g, unsigned char b);

    static Pixel Black();
    static Pixel Red();
    
private:
    RGBA _rgba;
};