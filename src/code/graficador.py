import matplotlib.pyplot as plt
import sys
import csv

data_path = "../../data/"


def graficar_listas(team_ids, cmms, labels, winrates):
	#labels = ['Frogs', 'Hogs', 'Bogs', 'Slogs']

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
	res = []
	with open(file, 'r') as f:
		for line in f:
			#print line
			res.append(float(line))
	return res

def read_labels(file):
	res = []
	with open(file, 'rb') as f:
		reader = csv.reader(f, delimiter=',')
		for row in reader:
			#print line
			res.append(row[1])
	return res

competencia = sys.argv[1]
if competencia == "nba":
	cmms = read_exp(data_path + "tests_cualitativos/nba_2016_scores.dat-1.out")
#print cmms[0:10]
	winrates = read_exp(data_path + "tests_cualitativos/nba_2016_scores.dat-2.out")
#print winrates[0:10]
	team_ids = range(0, len(cmms))
	labels = read_labels(data_path + "nba_2016_teams.csv")
#print team_ids[0:10]
elif competencia == "atp":
	cmms = read_exp(data_path + "tests_cualitativos/atp_matches_2015-1.out")[0:10]
#print cmms[0:10]
	winrates = read_exp(data_path + "tests_cualitativos/atp_matches_2015-2.out")[0:10]
#print winrates[0:10]
	team_ids = range(0, len(cmms))[0:10]
	labels = read_labels(data_path + "atp_players.csv")[0:10]
graficar_listas(team_ids, cmms, labels, winrates)