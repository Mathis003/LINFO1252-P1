from matplotlib import pyplot as plt
import pandas as pd
import numpy as np
import sys
import os

if len(sys.argv) != 2:
    print("Usage: name file <name_file>")
    sys.exit(1)

name_file = sys.argv[1]
csv_files = ["./csv_files/perfs_" + name_file + "_POSIX.csv", "./csv_files/perfs_" + name_file + "_TS.csv", "./csv_files/perfs_" + name_file + "_TTS.csv", "./csv_files/perfs_" + name_file + "_BTTS.csv"]

datas = [pd.read_csv(csv_files[0]), pd.read_csv(csv_files[1]), pd.read_csv(csv_files[2]), pd.read_csv(csv_files[3])]
nbThreads = datas[0]['NbThreads']

means = []
std_devs = []

for i in range(4):
    datas[i] = datas[i].drop('NbThreads', axis=1)
    datas[i] = datas[i].values

    means.append([np.mean(d) for d in datas[i]])
    std_devs.append([np.std(d) for d in datas[i]])

    datas[i] = datas[i].transpose()


plt.figure()

colors = ['lightblue', 'lightgreen', 'lightpink', 'lightgray', '', '', '']

for i in range(4):
    color = colors[i]

    boxplot = plt.boxplot(datas[i], vert=True, meanline=True, showmeans=True, patch_artist=True)
    plt.errorbar(range(1, len(nbThreads) + 1), means[i], yerr=std_devs[i], fmt='ro', markersize=2, label='Standard deviation')

    for patch, unused in zip(boxplot['boxes'], colors):
        patch.set_facecolor(color)


plt.xticks(np.arange(1, len(nbThreads) + 1), nbThreads)

plt.title("Time Performance Metrics [{}.c] vs. Number of Threads".format(name_file))
plt.xlabel('Number of Threads []')
plt.ylabel('Execution Time [s]')
plt.ylim(0)
plt.legend()
plt.grid()
plt.savefig("graphs/png/perfs_graph_" + name_file + ".png")
plt.savefig("graphs/pdf/perfs_graph_" + name_file + ".pdf")
plt.show()


plt.figure()

labels = ["POSIX", "test-and-set", "test-and-test-and-set", "backoff-test-and-test-and-set"]

for i in range(4):
    means = []
    for j in range(len(datas[i][0])):
        mean = 0
        for k in range(len(datas[i])):
            mean += datas[i][k][j]
        means.append(mean / len(datas[i]))
    plt.plot(nbThreads.values, means, label=labels[i])

plt.title("Time Performance Metrics [{}.c] vs. Number of Threads".format(name_file))
plt.xlabel('Number of Threads []')
plt.ylabel('Execution Time [s]')
plt.ylim(0)
plt.legend()
plt.grid()
plt.show()