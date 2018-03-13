from PyEXR import PyEXRImage

exrImage = PyEXRImage('2by2.exr')

print(exrImage.filename)
print(exrImage.width)
print(exrImage.height)
print(exrImage)

# Direct access to floats
for i in range(exrImage.width * exrImage.height):
    r = exrImage.get(4 * i + 0)
    g = exrImage.get(4 * i + 1)
    b = exrImage.get(4 * i + 2)
    a = exrImage.get(4 * i + 3)
    print(r,g,b,a)
print ('--------------------------')

# Access by index x,y,channel
for y in range(exrImage.width):
    for x in range(exrImage.height):
        r = exrImage.getPixel(x,y,0)
        g = exrImage.getPixel(x,y,1)
        b = exrImage.getPixel(x,y,2)
        a = exrImage.getPixel(x,y,3)

        print(r,g,b,a)
print ('--------------------------')

# Convert to NumPy 
import numpy as np
m = np.array(exrImage, copy = False)
print (m)
print ('--------------------------')

# Shape into x,y,channel matrix
t = np.reshape(m, (exrImage.width, exrImage.height, 4))
print (t)
print ('--------------------------')

print(t[0][0][:])
print(t[0][1][:])
print(t[1][0][:])
print(t[1][1][:])
