import sys
import re

filename = input ()
f = open (filename, 'r')
for line in f:
    [left_part, right_part] = line.split (":-")
    right_vars = re.split (",|\.", right_part)
    right_vars.pop (-1) #removes \n
