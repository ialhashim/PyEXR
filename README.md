# PyEXR
Loading OpenEXR (.exr) images using Python. 

It is basically a Python binding for tinyexr. Use CMake to build the module (uses pybind11). Installation script is not there, you can simply copy the resulting python module files. Supports loading functionality, saving can be easily added (pull requests welcome!).

# Usage
```python
from PyEXR import PyEXRImage 

# Load an EXR image (tinyexr backend)
img = PyEXRImage('2by2.exr')

# Print basic details
print(img) 

# Pixel values access
r = img.getPixel(x,y,0)
g = img.getPixel(x,y,1)
b = img.getPixel(x,y,2)
a = img.getPixel(x,y,3)

# Numpy:
m = np.array(img, copy = False)
# or
rgb = np.reshape(np.array(rgb_img, copy = False), (rgb_img.height, rgb_img.width, 4)) 
# a matrix of (height x width x channels)
    
# Display
from PIL import Image
Image.fromarray(np.clip(np.uint8(rgb*255.0), 0, 255)).show()
```
