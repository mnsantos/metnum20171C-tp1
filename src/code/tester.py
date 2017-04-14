import os
import sys
import matplotlib.pyplot as plt
import glob	
import time
import random
import subprocess

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

	results = []
	for i in range(minimo, maximo+1):
		for method in methods:
			entrada = './../data/tests_tiempos/generated_' + str(i) + '.dat'
			salida = '../../data/tests_tiempos/generated_' + str(i) + '-out-' + str(method)
			os.system('./../tp ' + entrada + ' ' + salida + ' ' + str(method))
			with open(name, 'w') as f:

			total_gauss = 
			total_cholesky = 

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