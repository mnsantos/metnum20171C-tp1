import matplotlib.pyplot as plt
import sys
import csv
import numpy as np


data_path = "../../data/"


def graficar_listas(team_ids, cmms, labels, winrates, competencia):
	#labels = ['Frogs', 'Hogs', 'Bogs', 'Slogs']

	team_ids = team_ids[0:15] if competencia == 'atp' else team_ids
	cmms = cmms[0:15] if competencia == 'atp' else cmms
	labels = labels[0:15] if competencia == 'atp' else labels
	winrates = winrates[0:15] if competencia == 'atp' else winrates

	plt.plot(team_ids, cmms, 'ro', label='Cmm')
	plt.plot(team_ids, winrates, 'bs', label='Winrate')
	# You can specify a rotation for the tick labels in degrees or with keywords.
	plt.xticks(team_ids, labels, rotation='vertical')
	# Pad margins so that markers don't get clipped by the axes
	plt.margins(0.2)
	plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3,
           ncol=2, mode="expand", borderaxespad=0.)
	# Tweak spacing to prevent clipping of tick-labels
	plt.subplots_adjust(bottom=0.15)
	plt.show()

def read_exp(file):
	ids = []
	rankings = []
	enfrentamientos = []
	with open(file, 'r') as f:
		reader = csv.reader(f, delimiter=' ')
		for row in reader:
			#print line
			ids.append(row[0])
			rankings.append(row[3])
			enfrentamientos.append(int(row[1]) + int(row[2]))
	return ids, rankings, enfrentamientos

def read_labels(file, comptencia, team_ids):
	res = []
	if comptencia == 'atp':
		with open(file, 'rb') as f:
			reader = csv.reader(f, delimiter=',')
			for row in reader:
				#print line
				res.append([row[0], row[1] + "," + row[2]])
	else:
		with open(file, 'rb') as f:
			reader = csv.reader(f, delimiter=',')
			for row in reader:
				#print line
				res.append([int(row[0]), row[1]])
	labels = []
	labelsMap = {}
	for team_id in team_ids:
		for r in res:
			if int(team_id) == int(r[0]):
				labels.append(r[1])
				labelsMap[team_id] = r[1]
	return labels, labelsMap

def generar_calendario(team_ids, competencia, labelsMap):
	rows = []
	with open(data_path + ("nba_2016_scores.dat" if competencia == "nba" else "atp_matches_2015.dat"), 'rb') as f:
		reader = csv.reader(f, delimiter=' ')
		for row in reader:
			if len(row) == 5:
				rows.append([row[1],row[3]])
	res = []
	for team_id in team_ids:
		enfrentamientos = {}
		for row in rows:
			if int(team_id) == int(row[0]):
				if row[1] in enfrentamientos:
					enfrentamientos[row[1]] = enfrentamientos[row[1]] + 1
				else:
					enfrentamientos[row[1]] = 1
			elif int(team_id) == int(row[1]):
				if row[0] in enfrentamientos:
					enfrentamientos[row[0]] = enfrentamientos[row[0]] + 1
				else:
					enfrentamientos[row[0]] = 1
		res.append(enfrentamientos)
	path = data_path + ("tests_cualitativos/nba_2016_scores.dat-schedule.csv" if competencia == "nba" else "tests_cualitativos/atp_matches_2015-schedule.csv") 
	first_row = [" "] + [labelsMap[team] for team in team_ids]
	with open(path, 'w') as f:
		writer = csv.writer(f, delimiter=',')
		writer.writerow(first_row)
		for enfrentamientos, team_id in zip(res, team_ids):
			row = [labelsMap[team_id]]
			for op in team_ids:
				if op in enfrentamientos:
					row.append(enfrentamientos[op])
				else:
					row.append(0)
			writer.writerow(row)
	return res

# def generar_tabla_enfrentamientos(team_ids, enfrentamientos, labelsMap, competencia):
# 	teams_ids_sorted, enfrentamientos_sorted = zip(*sorted(zip(team_ids, enfrentamientos), reverse=True))
# 	path = data_path + ("tests_cualitativos/nba_2016_scores.dat-enfrentamientos.csv" if competencia == "nba" else "tests_cualitativos/atp_matches_2015-enfrentamientos.csv") 
# 	with open(path, 'w') as f:
# 		writer = csv.writer(f, delimiter=',')
# 		writer.writerow(["Equipo" if competencia == 'nba' else "Jugador", "Enfrentamientos"])
# 		for t in zip(team_ids, enfrentamientos):
# 			writer.writerow([labelsMap[t[0]], t[1]])

def generar_tabla_enfrentamientos(enfrentamientos, labels, rankings, competencia, metodo, team_ids):
	rankings_sorted, team_ids_sorted, labels_sorted, enfrentamientos_sorted = zip(*sorted(zip(rankings, team_ids, labels, enfrentamientos), reverse=True))
	path = "tests_cualitativos/atp_matches_2015-" + str(metodo) + "-enfrentamientos.csv" if competencia == "atp" else "tests_cualitativos/nba_2016_scores.dat-" + str(metodo) + "-enfrentamientos.csv"
	tuples = zip(labels_sorted, enfrentamientos_sorted)
	with open(data_path + path, 'w') as f:
		writer = csv.writer(f, delimiter=',')
		writer.writerow(["Equipo" if competencia == 'nba' else "Jugador", "Enfrentamientos"])
		for t in tuples:
			writer.writerow(t)

def generar_tabla_posiciones(team_ids, labels, rankings, competencia, metodo):
	rankings_sorted, team_ids_sorted, labels_sorted = zip(*sorted(zip(rankings, team_ids, labels), reverse=True))
	path = "tests_cualitativos/atp_matches_2015-" + str(metodo) + "-positions.csv" if competencia == "atp" else "tests_cualitativos/nba_2016_scores.dat-" + str(metodo) + "-positions.csv"
	tuples = zip(range(1,len(team_ids)), labels_sorted, rankings_sorted)
	with open(data_path + path, 'w') as f:
		writer = csv.writer(f, delimiter=',')
		writer.writerow(["Posicion", "Equipo" if competencia == 'nba' else "Jugador", metodo])
		for t in tuples:
			writer.writerow(t)

competencia = sys.argv[1]
if competencia == "nba":
	team_ids, cmms, enfrentamientos = read_exp(data_path + "tests_cualitativos/nba_2016_scores.dat-1.out-exp")
	team_ids, winrates, enfrentamientos = read_exp(data_path + "tests_cualitativos/nba_2016_scores.dat-2.out-exp")
	labels, labelsMap = read_labels(data_path + "nba_2016_teams.csv", "nba", team_ids)
	schedules = generar_calendario(team_ids, competencia, labelsMap)
	team_ids = range(1, len(cmms)+1)
	generar_tabla_enfrentamientos(enfrentamientos, labels, cmms, competencia, "CMM", team_ids)
	generar_tabla_enfrentamientos(enfrentamientos, labels, winrates, competencia, "Winrate", team_ids)
	generar_tabla_posiciones(team_ids, labels, cmms, competencia, "CMM")
	generar_tabla_posiciones(team_ids, labels, winrates, competencia, "Winrate")
elif competencia == "atp":
	team_ids, cmms, enfrentamientos = read_exp(data_path + "tests_cualitativos/atp_matches_2015-1.out-exp")
	team_ids, winrates, enfrentamientos = read_exp(data_path + "tests_cualitativos/atp_matches_2015-2.out-exp")
	labels, labelsMap = read_labels(data_path + "atp_players.csv", "atp", team_ids)
	schedules = generar_calendario(team_ids, competencia, labelsMap)
	team_ids = range(1, len(cmms)+1)
	generar_tabla_enfrentamientos(enfrentamientos, labels, cmms, competencia, "CMM", team_ids)
	generar_tabla_enfrentamientos(enfrentamientos, labels, winrates, competencia, "Winrate", team_ids)
	generar_tabla_posiciones(team_ids, labels, cmms, competencia, "CMM")
	generar_tabla_posiciones(team_ids, labels, winrates, competencia, "Winrate")
graficar_listas(team_ids, cmms, labels, winrates, competencia)


