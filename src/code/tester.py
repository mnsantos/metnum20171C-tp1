import os
import sys
import matplotlib.pyplot as plt
import glob	
import time
import random

methods = [0, 1]
data_path = "../../data/time_tests/"
results_path = "results.txt"

def generar_instancia(n):
	k = n * (n-1)
	lines = [[n, k]]	
	for i in range(1, n+1):
		for j in range(1, n+1):
			if j != i:
				lines.append([1, i, random.randint(0,9), j, random.randint(0,9)])
	return lines


def guardar_instancia(instancia):
	name = data_path + 'generated_' + str(len(instancia) - 1) + '.dat'
	with open(name, 'w') as f:
		for line in instancia:
			f.write(' '.join([str(l) for l in line]))
			f.write('\n')

def fabricar_instancias(min_equipos, max_equipos):
	instancias = [generar_instancia(i) for i in range(min_equipos,max_equipos+1)]
	for inst in instancias:
		guardar_instancia(inst)

def test():
	os.chdir("..")
	os.system('python metnum.py build')
	os.chdir("code")
	files = glob.glob(data_path + '*.dat')
	for fname in files:
		for method in methods:
			os.system('./../tp '+ fname + ' ' + fname + '.out ' + str(method))

if __name__ == '__main__':
	os.system('rm ' + data_path + "*")
	fabricar_instancias(int(sys.argv[1]), int(sys.argv[2]))
	test()
	#time_tests(sys.argv[3])
	#time_tests('out')