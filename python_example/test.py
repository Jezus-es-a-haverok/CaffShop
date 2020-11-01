import python_example
import numpy as np

a = np.ones((10,4)) * 2
b = np.ones((10,4)) * 3
c = python_example.add_arrays(a, b)

print(c)
