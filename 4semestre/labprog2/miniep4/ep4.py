import unittest
import math

class TestMathFunctions(unittest.TestCase):
    eps = 1e-7
    epsc = 1e-500
    pi = 3.141592653589793238462643383279

    def setUp(self):
        self.entries = list(range(100))

    def my_sen(self, x):
        s = x
        term = x
        i = 1
        while (abs(term) > self.epsc):
            term = term * x * x * (-1)
            term = term / ((i + 1) * (i + 2))
            s = s + term
            i = i + 2
        return s

    def test_sen(self):
        #verificar que sen(x) == sen(2pi + x)
        for x in self.entries:
            self.assertAlmostEqual(math.sin(x), math.sin(2 * self.pi + x), delta = self.eps)
        
        #verificar se |sen(x)| == |sen(-x)|
        for x in self.entries:
            self.assertAlmostEqual(abs(math.sin(x)), abs(math.sin(-x)), delta = self.eps)

        

if __name__ == '__main__':
    unittest.main()
