# PyEXR
Loading OpenEXR (.exr) images using Python. 

It is basically a Python binding for tinyexr. Use CMake to build the module (uses pybind11). Installation script is not there, you can simply copy the resulting python module files.

# Usage
```python
from PyEXR import PyEXRImage 

# Load an EXR image (tinyexr backend)
img = PyEXRImage('2by2.exr')

# Print basic details
print(exrImage) 

# Pixel values access
r = img.getPixel(x,y,0)
g = img.getPixel(x,y,1)
b = img.getPixel(x,y,2)
a = img.getPixel(x,y,3)

# Numpy:
m = np.array(img, copy = False)
# or
m = np.reshape(m, (img.width, img.height, 4)) # matrix (width x height x channels)
```
