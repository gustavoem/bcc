import tensorflow as tf

global input_size 
input_size = 3.0

X = tf.placeholder ("float", [input_size], 'X')
result = tf.tanh (X)

sess = tf.Session ()
print (sess.run (result, {X: [1, .2, -1]}))
