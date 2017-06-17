# Inspired on the tutorial available at: 
# https://www.analyticsvidhya.com/blog/2016/04/neural-networks-python-theano/

import numpy as np
import theano.tensor as T
import theano
from theano.ifelse import ifelse
from random import random

inputs = [
        [0, 0],
        [0, 1],
        [1, 0],
        [1, 1],
        [0, 0],
        [0, 1],
        [1, 0],
        [1, 1]]]
outputs = [0, 0, 0, 1, 0, 0, 0, 1]

x = T.matrix ('x')
w = theano.shared (np.array ([random (), random ()]))
b = theano.shared (1.)
learning_rate = .01
bias = random ()

signal = T.dot (x, w) + b
theta = theano.tensor.tanh (signal)
neuron = theano.function ([x], a)

y = T.vector ('y')
e_in = ((y - theta) ** 2).sum ()
dw, db = T.grad (e_in, [w, b])


for i in range (len (inputs)):
    t = inputs[i]
    out = neuron (t)
    print ("output is " + str (out))



