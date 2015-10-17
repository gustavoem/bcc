class Buzina:
	def __init__(self):
		print("init da buzina")
	def aperta(self):
		print("Foommm!")

class Vuvuzela(Buzina):
	def __init__(self):
		print("init da vuvuzela")
	def aperta(self):
		for i in range(10):
			super().aperta()



print("Lixo")

class Veiculo():
	def __init__(self):
		self.buzina = Buzina()
	def vai_para_frente(self):
		print("Vai para frente")
	def para(self):
		print("Carro parado")
	def buzinar(self):
		self.buzina.aperta()
		


ford_t = Veiculo()
ford_t.vai_para_frente()
ford_t.para()

class VeiculoModerno(Veiculo):
	def vai_para_tras(self):
		print("Vai para tras")

fusca = VeiculoModerno()
fusca.vai_para_tras()
fusca.vai_para_frente()

class VeiculoConversivel(VeiculoModerno):
	def abre_capota(self):
		print("Abri a capota")
	def fecha_capota(self):
		print("Fechou a capota")
	def vai_para_frente(self):
		print("VAI PRA FRENTE")

ferrari = VeiculoConversivel()
ferrari.abre_capota()
ferrari.vai_para_frente()

def veiculo_anda_para_frente(veiculo):
	veiculo.vai_para_frente()

veiculo_anda_para_frente(ford_t)
veiculo_anda_para_frente(fusca)
veiculo_anda_para_frente(ferrari)

mustang = VeiculoConversivel()
mustang.buzinar()
