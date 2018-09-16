#pragma once

#include <string>
#include <vector>

struct PyEXRImage
{
    PyEXRImage(const std::string &filename);
    PyEXRImage(int width, int height);
	~PyEXRImage();

    float getPixel(int x, int y, int channel);
    float get(int i);
    float *data() { return out_rgba; }

    void set(int i, int channel, float value);
    void save(const std::string &filename);

    std::string filename;
    float* out_rgba; // width * height * RGBA
    int width;
    int height;
    int ret;
    const char* err;
};
