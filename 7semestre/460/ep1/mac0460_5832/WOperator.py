import numpy as np

class WOperator:
    """ Class used to define a W-Operator """

    def __init__ (self, f):
        """ Class constructor. 
            n stands for window height
            m stands for window length """
        self.f = f

    def operate_image (self, img):
        """ Operates over an image """
