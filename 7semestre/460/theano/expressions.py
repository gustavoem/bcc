# Inspired on the tutorial available at: 
# https://www.analyticsvidhya.com/blog/2016/04/neural-networks-python-theano/

import numpy as np
import theano.tensor as T
from theano import function
from theano import shared

# define variables
a = T.dscalar ('a')
b = T.dscalar ('b')

# define expressions
c = a * b
f = function ([a, b], c)

# evaluate
print (f (4.5, 8))

# defines a constant
x = T.iscalar ('x')
sh = shared (0)
f = function ([x], sh ** 2, updates = [(sh, sh + x)])
print (f (1))  # 0 ** 2 = 0
print (f (2))  # 1 ** 2 = 1
print (f (1))  # 3 ** 2 = 9
print (sh.get_value ()) # 4


