from matplotlib import pyplot as plt
import pandas as pd
import numpy as np
import sys
import os

csv_files = ["./csv_files/perfs_main_my_mutex_TS.csv", "./csv_files/perfs_main_my_mutex_TTS.csv", "./csv_files/perfs_main_my_mutex_BTTS.csv"]

datas = [pd.read_csv(csv_files[0]), pd.read_csv(csv_files[1]), pd.read_csv(csv_files[2])]
means = []
std_devs = []
nbThreads = datas[0]['NbThreads']

for i in range(3):
    datas[i] = datas[i].drop('NbThreads', axis=1)
    datas[i] = datas[i].values
    datas[i] *= 1000

    means.append([np.mean(d) for d in datas[i]])
    std_devs.append([np.std(d) for d in datas[i]])

    datas[i] = datas[i].transpose()


plt.figure()

boxplots = []
colors = ['lightblue', 'lightgreen', 'lightpink', '', '', '', '']

for i in range(3):
    color = colors[i]
    boxplot = plt.boxplot(datas[i], vert=True, meanline=True, showmeans=True, patch_artist=True)
    plt.errorbar(range(1, len(nbThreads) + 1), means[i], yerr=std_devs[i], fmt='ro', markersize=2, label='Standard deviation')
    
    for patch, unused in zip(boxplot['boxes'], colors):
        patch.set_facecolor(color)


plt.xticks(np.arange(1, len(nbThreads) + 1), nbThreads)

plt.title("Time Performance Metrics [main_my_mutex.c] vs. Number of Threads")
plt.xlabel('Number of Threads []')
plt.ylabel('Execution Time [ms]')
plt.ylim(0)
plt.legend()
plt.grid()
plt.savefig("graphs/png/perfs_graph_mutex.png")
plt.savefig("graphs/pdf/perfs_graph_mutex.pdf")
plt.show()




plt.figure()

labels = ["test-and-set", "test-and-test-and-set", "backoff-test-and-test-and-set"]

for i in range(3):
    means = []
    for j in range(len(datas[i][0])):
        mean = 0
        for k in range(len(datas[i])):
            mean += datas[i][k][j]
        means.append(mean / len(datas[i]))
    plt.plot(nbThreads.values, means, label=labels[i])

plt.title("Time Performance Metrics [main_my_mutex.c] vs. Number of Threads")
plt.xlabel('Number of Threads []')
plt.ylabel('Execution Time [ms]')
plt.ylim(0)
plt.legend()
plt.grid()
plt.show()