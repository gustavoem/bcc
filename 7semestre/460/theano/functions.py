# Inspired on the tutorial available at: 
# https://www.analyticsvidhya.com/blog/2016/04/neural-networks-python-theano/

import numpy as np
import theano.tensor as T
from theano import function
from theano import shared
from theano import pp # pretty-print

# multiple output
a = T.dscalar ('a')
f = function ([a], [a ** 2, a ** 3])
print (f(3))

# computing gradients
x = T.dscalar ('x')
y = x ** 3
qy = T.grad (y, x) # qy = 3x ^ 2
f = function ([x], qy)
g = function ([x], y)
print (f (2))
print (g (3))
print (pp(qy))
