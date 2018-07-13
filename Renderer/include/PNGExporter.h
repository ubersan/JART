#pragma once

#include <vector>

class PNGExporter
{
public:
    static void Export(const std::vector<unsigned char>& imageData, int width, int height);
};