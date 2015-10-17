for i in range(4):
	try:
		print(lista[i])
	except IndexError:
		i = 0
class NaoEInteiro(Exception):
	pass
