#pragma once

#include <string>
#include <vector>

struct PyEXRImage
{
    PyEXRImage(const std::string &filename);
    std::string filename;

    float getPixel(int x, int y, int channel);
    float get(int i);
    float *data() { return out_rgba; }

    float* out_rgba; // width * height * RGBA
    int width;
    int height;
    int ret;
    const char* err;
};
