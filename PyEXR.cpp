#include "PyEXR.h"

#define TINYEXR_IMPLEMENTATION
#include "tinyexr.h"

PyEXRImage::PyEXRImage(const std::string &filename) :
    width(-1), height(-1), out_rgba(nullptr), filename(filename)
{
    ret = LoadEXR(&out_rgba, &width, &height, filename.c_str(), &err);
}

PyEXRImage::PyEXRImage(int width, int height) :
    width(width), height(height), out_rgba(nullptr)
{
    auto size = 4 * static_cast<size_t>(width) * static_cast<size_t>(height);
    out_rgba = reinterpret_cast<float *>(malloc(sizeof(float) * size));

    for(size_t i = 0; i < size; ++i){
        out_rgba[i] = 1.0f;
    }
}

void PyEXRImage::save(const std::string &filename)
{
    SaveEXR(out_rgba, width, height, 4, 1, filename.c_str());
}

float PyEXRImage::getPixel(int x, int y, int channel)
{
    auto line_width = width * 4;
    auto pixel_idx = (y * line_width) + (x * 4);
    return out_rgba[pixel_idx + channel];
}

float PyEXRImage::get(int i)
{
    return out_rgba[i];
}

void PyEXRImage::set(int i, int channel, float value)
{
    out_rgba[i*4 + channel] = value;
}

/* Python Binding */
#include <pybind11/pybind11.h>
namespace py = pybind11;

PYBIND11_MODULE(PyEXR, m) {
    m.doc() = "EXR image files reader";
    py::class_<PyEXRImage>(m, "PyEXRImage", py::dynamic_attr(), py::buffer_protocol())
            .def(py::init<const std::string &>())
            .def(py::init<int,int>())
            .def("getPixel", &PyEXRImage::getPixel, "Get a pixel's RGBA values", py::arg("x"), py::arg("y"), py::arg("channel"))
            .def("get", &PyEXRImage::get)
            .def("set", &PyEXRImage::set, "Set pixel value", py::arg("i"), py::arg("channel"), py::arg("value"))
            .def("save", &PyEXRImage::save)
            .def_readwrite("width", &PyEXRImage::width)
            .def_readwrite("height", &PyEXRImage::height)
            .def_readwrite("filename", &PyEXRImage::filename)
            .def_readwrite("ret", &PyEXRImage::ret)
            .def_readwrite("err", &PyEXRImage::err)
            .def("__repr__",
                [](const PyEXRImage &m) {
                    return "<EXR Image " + std::to_string(m.width) + "x" + std::to_string(m.height) + " '" + m.filename + "'>";
                }
            )
            .def_buffer([](PyEXRImage &m) -> py::buffer_info {
                return py::buffer_info(
                    m.data(),                                   /* Pointer to buffer */
                    sizeof(float),                              /* Size of one scalar */
                    py::format_descriptor<float>::format(),     /* Python struct-style format descriptor */
                    1,                                          /* Number of dimensions */
                    { m.width * m.height * 4 },                 /* Buffer dimensions */
                    { sizeof(float)}                            /* Strides (in bytes) for each index */
                );
            });
}
