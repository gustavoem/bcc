def f(a):
	a = 3

a = 2
f(a)
print(a)

class Teste:
	def f(self, val):
		self.val = val

num = Teste()
num.val = 321
print(num.val)
num.f(123)
print(num.val)