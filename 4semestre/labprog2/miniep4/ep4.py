import unittest
import math
import random

class TestMathFunctions(unittest.TestCase):
    eps = 1e-7
    epsc = 1e-50
    pi = 3.141592653589793238462643383279
    ln2 = 0.69314718056

    def setUp(self):
        self.rnd_ints = []
        for i in range (100):
            self.rnd_ints.append(random.randrange(1, 1000))


    def my_sen(self, x):
        s = x
        term = x
        i = 1
        while abs(term) > self.epsc:
            term = term * x * x * (-1)
            term = term / ((i + 1) * (i + 2))
            s = s + term
            i = i + 2
        return s

    def my_cos(self, x):
        s = 1
        term = 1
        i = 0
        while abs(term) > self.epsc: 
            term = term * x * x * (-1)
            term = term / ((i + 1) * (i + 2))
            s = s + term
            i = i + 2
        return s

    def my_atan(self, x):
        s = x
        term = x
        i = 3
        while abs(term) > self.epsc:
            term = term * x * x * (-1)
            s = s + term / i
            i = i + 2
        return s

    def my_log2(self, x):
        term = -1 / self.ln2
        s = 0
        i = 1
        while abs(term) > 0:
            term = term * (x - 1) * (-1) 
            s = s + term / i
            i = i + 1
        return s

    def my_factorial(self, x):
        p = 1
        for i in range(x):
            p = p * (i + 1)
        return p

    def test_sen(self):
        #verificar que sen(x) == sen(2pi + x)
        for x in self.rnd_ints:
            self.assertAlmostEqual(math.sin(x / 1000), math.sin(2 * self.pi + x / 1000), delta = self.eps)
        
        #verificar se sen(-x) == -sen(x)
        for x in self.rnd_ints:
            self.assertAlmostEqual(math.sin(-x / 1000), -math.sin(x / 1000), delta = self.eps)
        
        #verificar que sen(kpi) vale: 
        #0 se k = 4n ou k = 4n + 2
        #1 se k = 4n + 1
        #-1 se k = 4n + 2
        for x in self.rnd_ints:
            if x % 4 is 0 or x % 4 is 2:
                self.assertAlmostEqual(math.sin((self.pi * x) / 2), 0, delta = self.eps)
            elif x % 4 is 1:
                self.assertAlmostEqual(math.sin((self.pi * x) / 2), 1, delta = self.eps)
            else:
                self.assertAlmostEqual(math.sin((self.pi * x) / 2), -1, delta = self.eps)

        #verifica se levanta uma exceção quando mandamos algo que nao é número
        a = object()
        self.assertRaises(TypeError, math.sin, a)
        
        #verifica se a função que está em math tem os mesmos resultados que a função my_sen para 100 valores entre 0 e 1: (0.01 0.02 ... 1)
        for x in self.rnd_ints:
            self.assertAlmostEqual(math.sin(x / 1000), self.my_sen(x / 1000), delta = self.eps)

    def test_atan(self):
        #verificar se a função que está em math é de fato a inversa de tg(x) para valores entre 0 e 1: (0.01 0.02 ... 1)
        for x in self.rnd_ints:
            self.assertAlmostEqual(math.atan(self.my_sen(x / 1000) / self.my_cos(x / 1000)), x / 1000, delta = self.eps)

        #verifica se a função dá os mesmos resultados que a função my_atan para valores entre 0 e 1
        for x in self.rnd_ints:
            self.assertAlmostEqual(math.atan(x / 1000), self.my_atan(x / 1000), delta = self.eps)

        #verificar que para valor muito alto a função vale perto de pi / 2
        self.assertAlmostEqual(math.atan(1e10), self.pi / 2, delta = self.eps)

        #verificar que no zero vale zero
        self.assertAlmostEqual(math.atan(0), 0, delta = self.eps)

        #verificar se levanta uma exceção quando mandamos algo que não é número
        a = object()
        self.assertRaises(TypeError, math.atan, a)

    def test_factorial(self):
        #verifica que fatorial de 0 é um
        self.assertEqual(math.factorial(0), 1)
        
        #verifica se a função que está em math da os mesmos resultados que a função my_factorial para valores inteiros entre 0 e 10
        for x in range(11):
            self.assertEqual(math.factorial(x), self.my_factorial(x))

        #verificar se levanta exceção quando mandamos algo que não é número
        a = object()
        self.assertRaises(TypeError, math.factorial, a)

        #verifica se levanta exceção quando mandamos numeros negativos
        for x in self.rnd_ints:
            self.assertRaises(ValueError, math.factorial, -(x + 1))

        #verifica se levanta exceção quando mandamos numeros quebrados
        for x in self.rnd_ints:
            self.assertRaises(ValueError, math.factorial, 0.0001 + x / 1000)

    def test_log2(self):
        #verifica se a função que está em math da os mesmos resultados que a função my_log2 para 100 valores entre 0.5 e 1.5
        for x in self.rnd_ints:
            self.assertAlmostEqual(math.log2(x / 1000 + 0.50), self.my_log2(x / 1000 + 0.50), delta = self.eps)

        #verificar se levanta exceção quando mandamos algo que não é número
        a = object()
        self.assertRaises(TypeError, math.log2, a)

        #verifica se levanta exceção quando mandamos numeros menores ou iguais a zero
        for x in self.rnd_ints:
            self.assertRaises(ValueError, math.log2, -x)
        
        #verifica se levanta exceção quando mandamos zero
        self.assertRaises(ValueError, math.log2, 0)
            
if __name__ == '__main__':
    unittest.main()
