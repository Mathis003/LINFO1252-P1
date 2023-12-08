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

colors = ['lightblue', 'lightgreen', 'lightpink', '#ff9999', '#99ff99', '#ffcc99', '#c2c2f0', '#ffb3e6']

plt.figure(figsize=(10, 12))

# First subplot
plt.subplot(2, 2, 4)

boxplot = plt.boxplot(datas[0], vert=True, meanline=True, showmeans=True, patch_artist=True)
plt.errorbar(range(1, len(nbThreads) + 1), means[0], yerr=std_devs[0], fmt='ro', markersize=2, label='Standard deviation')
for patch, color in zip(boxplot['boxes'], colors):
    patch.set_facecolor(color)

median_patch = plt.Line2D([0, 1], [0, 0], color='#FFA500', linewidth=1, linestyle='solid', label='Median')
mean_patch = plt.Line2D([0, 1], [0, 0], color='green', linewidth=1, linestyle='dashed', label='Mean')
std_patch = plt.Line2D([0, 0], [0, 1], marker='o', color='red', linewidth=1, linestyle='solid', markersize=2, label='Standard deviation')

plt.title("POSIX implementation")
plt.xticks(np.arange(1, len(nbThreads) + 1), nbThreads)
plt.ylim(0)
plt.legend(handles=[median_patch, mean_patch, std_patch])
plt.grid()

# Second subplot
plt.subplot(2, 2, 2)

boxplot = plt.boxplot(datas[1], vert=True, meanline=True, showmeans=True, patch_artist=True)
plt.errorbar(range(1, len(nbThreads) + 1), means[1], yerr=std_devs[1], fmt='ro', markersize=2, label='Standard deviation')
for patch, color in zip(boxplot['boxes'], colors):
    patch.set_facecolor(color)

median_patch = plt.Line2D([0, 1], [0, 0], color='#FFA500', linewidth=1, linestyle='solid', label='Median')
mean_patch = plt.Line2D([0, 1], [0, 0], color='green', linewidth=1, linestyle='dashed', label='Mean')
std_patch = plt.Line2D([0, 0], [0, 1], marker='o', color='red', linewidth=1, linestyle='solid', markersize=2, label='Standard deviation')

plt.title("Test And Set algorithm")
plt.xticks(np.arange(1, len(nbThreads) + 1), nbThreads)
plt.ylim(0)
plt.legend(handles=[median_patch, mean_patch, std_patch])
plt.grid()


# Third subplot
plt.subplot(2, 2, 3)

boxplot = plt.boxplot(datas[2], vert=True, meanline=True, showmeans=True, patch_artist=True)
plt.errorbar(range(1, len(nbThreads) + 1), means[2], yerr=std_devs[2], fmt='ro', markersize=2, label='Standard deviation')
for patch, color in zip(boxplot['boxes'], colors):
    patch.set_facecolor(color)

median_patch = plt.Line2D([0, 1], [0, 0], color='#FFA500', linewidth=1, linestyle='solid', label='Median')
mean_patch = plt.Line2D([0, 1], [0, 0], color='green', linewidth=1, linestyle='dashed', label='Mean')
std_patch = plt.Line2D([0, 0], [0, 1], marker='o', color='red', linewidth=1, linestyle='solid', markersize=2, label='Standard deviation')

plt.title("Test And Test And Set algorithm")
plt.xticks(np.arange(1, len(nbThreads) + 1), nbThreads)
plt.ylim(0)
plt.legend(handles=[median_patch, mean_patch, std_patch])
plt.grid()
plt.ylabel('Execution Time [ms]')


# Fourth subplot
plt.subplot(2, 2, 4)

boxplot = plt.boxplot(datas[3], vert=True, meanline=True, showmeans=True, patch_artist=True)
plt.errorbar(range(1, len(nbThreads) + 1), means[3], yerr=std_devs[3], fmt='ro', markersize=2, label='Standard deviation')
for patch, color in zip(boxplot['boxes'], colors):
    patch.set_facecolor(color)

median_patch = plt.Line2D([0, 1], [0, 0], color='#FFA500', linewidth=1, linestyle='solid', label='Median')
mean_patch = plt.Line2D([0, 1], [0, 0], color='green', linewidth=1, linestyle='dashed', label='Mean')
std_patch = plt.Line2D([0, 0], [0, 1], marker='o', color='red', linewidth=1, linestyle='solid', markersize=2, label='Standard deviation')

plt.title("Backoff Test And Test And Set algorithm")
plt.xticks(np.arange(1, len(nbThreads) + 1), nbThreads)
plt.xlabel('Number of Threads []')
plt.ylim(bottom=0, top=100)
plt.legend(handles=[median_patch, mean_patch, std_patch])
plt.grid()


plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.1, hspace=0.3, wspace=0.3)
plt.suptitle("Time Performance Metric [{}.c] vs. Number of Threads".format(name_file))

plt.savefig("graphs/png/perfs_graph_{}.png".format(name_file))
plt.savefig("graphs/pdf/perfs_graph_{}.pdf".format(name_file))
plt.show()