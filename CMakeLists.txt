project (PyEXR)
include_directories(tinyexr)
add_subdirectory(pybind11)
pybind11_add_module(PyEXR PyEXR.cpp)
