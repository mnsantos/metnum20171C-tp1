import os
import sys
import matplotlib.pyplot as plt
import glob	
import time
import random
import subprocess
import csv

methods = [0, 1]
data_path = "../../data/tests_tiempos/"
results_path = "results.txt"

def generar_instancia(n):
	k = n * (n-1)
	lines = [[n, k]]	
	for i in range(1, n+1):
		for j in range(1, n+1):
			if j != i:
				lines.append([1, i, random.randint(0,9), j, random.randint(0,9)])
	return lines, n


def guardar_instancia(instancia):
	name = data_path + 'generated_' + str(instancia[1]) + '.dat'
	with open(name, 'w') as f:
		for line in instancia[0]:
			f.write(' '.join([str(l) for l in line]))
			f.write('\n')

def fabricar_instancias(min_equipos, max_equipos, salto):
	instancias = [generar_instancia(i) for i in range(min_equipos,max_equipos+1,salto)]
	for inst in instancias:
		guardar_instancia(inst)

def test(minimo, maximo, salto):
	os.chdir("..")
	os.system('python metnum.py build')
	os.chdir("code")

	totales_gauss = []
	totales_cholesky = []
	# for i in range(minimo, maximo+1, salto):
	# 	entrada = '../../data/tests_tiempos/generated_' + str(i) + '.dat'
	# 	salida = '../../data/tests_tiempos/generated_' + str(i) + '-out'
	# 	os.system('./../tp ' + entrada + ' ' + salida + ' 1')
	# 	#print './../tp ' + entrada + ' ' + salida + ' ' + str(method)
	# 	with open(salida + '-time_tests', 'rb') as f:
	# 		reader = csv.reader(f, delimiter=' ')
	# 		for row in reader:
	# 			total_gauss = [i, row[0]]
	# 			total_cholesky = [i, row[1]]
	# 			totales_gauss.append(total_gauss)
	# 			totales_cholesky.append(total_cholesky)

	for i in range(minimo, maximo+1, salto):
		entrada = '../../data/tests_tiempos/generated_' + str(i) + '.dat'
		salida = '../../data/tests_tiempos/generated_' + str(i) + '-out'
		os.system('./../tp ' + entrada + ' ' + salida + ' 1')
		#print './../tp ' + entrada + ' ' + salida + ' ' + str(method)
		with open(salida + '-time_tests', 'rb') as f:
			reader = csv.reader(f, delimiter=' ')
			for row in reader:
				total_gauss = row[0]
				total_cholesky = row[1]
				totales_gauss.append(total_gauss)
				totales_cholesky.append(total_cholesky)
	printTiempos_2(zip(range(1, len(totales_cholesky)+1), totales_cholesky), zip(range(1, len(totales_cholesky)+1), totales_gauss), 'prueba')

def printTiempos_2(tiemposCholesky, tiemposGauss, filename):
	print tiemposCholesky
	print tiemposGauss
	# X = [ x[0] for x in tiemposCholesky ]
	# Y = [ x[1] for x in tiemposCholesky ]
	# plt.plot(X, Y, label='Cholesky')
	X = [ x[0] for x in tiemposGauss ] 
	Y = [ x[1] for x in tiemposGauss ]
	plt.plot(X, Y, label='Gauss')
	#plt.title(title)
	plt.xlabel('Iteracion')
	plt.ylabel('Tiempo en milisegundos')
	plt.grid(True)
	plt.legend(loc='upper center', shadow=True)
	plt.savefig(data_path+filename+".png")
	plt.close()
	#plt.show()

def printTiempos(tiemposCholesky, tiemposGauss, filename):
	X = [ x[0] for x in tiemposCholesky ]
	Y = [ x[1] for x in tiemposCholesky ]
	plt.plot(X, Y, label='Cholesky')
	X = [ x[0] for x in tiemposGauss ]
	Y = [ x[1] for x in tiemposGauss ]
	plt.plot(X, Y, label='Gauss')
	#plt.title(title)
	plt.xlabel('Cantidad de equipos')
	plt.ylabel('Tiempo en milisegundos')
	plt.grid(True)
	plt.legend(loc='upper center', shadow=True)
	plt.savefig(data_path+filename+".png")
	plt.close()
	#plt.show()

	#files = glob.glob(data_path + '*.dat')

	# for fname in files:
	# 	for method in methods:
	# 		os.system('./../tp '+ fname + ' ' + fname + '.out ' + str(method))

if __name__ == '__main__':
	minimo = int(sys.argv[1])
	maximo = int(sys.argv[2])
	salto = int(sys.argv[3])
	os.system('rm ' + data_path + "*")
	fabricar_instancias(minimo, maximo, salto)
	test(minimo, maximo, salto)
	#time_tests(sys.argv[3])
	#time_tests('out')