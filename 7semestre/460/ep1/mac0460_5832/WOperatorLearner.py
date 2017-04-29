import numpy as np
from mac0460_5832.utils import *

class WOperatorLearner:
    """ Class used to learn a biniary image operator """


    def __init__ (self, n, m):
        """ Class constructor """
        self.window_shape = (n, m)
        self.samples = {}


    def sample_image (self, src, dest):
        bsrc = self._zero_border_img (src)
        draw_img (bsrc)
        x_offset = int ((self.window_shape[1] - 1) / 2)
        y_offset = int ((self.window_shape[0] - 1) / 2)
        window_configuration = []
        sy, ey = 0, 2 * y_offset + 1
        for i in range (y_offset, y_offset + src.shape[0]):
            sx, ex = 0, 2 * x_offset + 1
            for j in range (x_offset, x_offset + src.shape[1]):
                window = np.array_str (bsrc[sy:ey, sx:ex])
                label = dest[i - y_offset][j - x_offset]
                if (window not in self.samples):
                    self.samples[window] = [0, 0]
                self.samples[window][label] += 1
                sx += 1
                ex += 1
            sy += 1
            ey += 1
        print (self.samples)
                
    def _zero_border_img (self, img):
        h = img.shape[0]
        w = img.shape[1]
        y_offset = int ((self.window_shape[0] - 1) / 2)
        x_offset = int ((self.window_shape[1] - 1) / 2)
        new_h = h + 2 * y_offset
        new_w = w + 2 * x_offset
        zeros = np.zeros ((new_h, new_w))
        bordered_img = zeros
        y_start, y_end = y_offset, -y_offset
        (x_start, x_end) = (x_offset, -x_offset)
        if y_offset is 0: y_end = h
        if x_offset is 0: x_end = w
        bordered_img[y_start:y_end, x_start:x_end] += img
        return bordered_img


