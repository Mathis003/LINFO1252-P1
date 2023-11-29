from matplotlib import pyplot as plt
import pandas as pd
import numpy as np
import sys
import os

if len(sys.argv) != 2:
    print("Usage: python script.py <csv_file>")
    sys.exit(1)

csv_file = sys.argv[1]

if not os.path.isfile(csv_file):
    print(f"Error: The file {csv_file} doesn't exist.")
    sys.exit(1)

if not csv_file.lower().endswith('.csv'):
    print(f"Error: The file {csv_file} isn't a CSV file.")
    sys.exit(1)

csv_file_name = os.path.splitext(os.path.basename(csv_file))[0]
program_name = csv_file_name[6:]

data = pd.read_csv(csv_file)
nbThreads = data['NbThreads']
data = data.drop('NbThreads', axis=1)
data = data.values

means = [np.mean(d) for d in data]
std_devs = [np.std(d) for d in data]

data = data.transpose()

unity_time = "s"
if np.max(data) < 1:
    unity_time = "ms"
    data *= 1000
    means = np.multiply(means, 1000)
    std_devs = np.multiply(std_devs, 1000)

plt.figure()

boxplot = plt.boxplot(data, vert=True, meanline=True, showmeans=True, patch_artist=True)

plt.errorbar(range(1, len(nbThreads) + 1), means, yerr=std_devs, fmt='ro', markersize=2, label='Standard deviation')

colors = ['lightblue', 'lightgreen', 'lightyellow', 'lightpink', 'lightgray']

for patch, color in zip(boxplot['boxes'], colors):
    patch.set_facecolor(color)

plt.xticks(np.arange(1, len(nbThreads) + 1), nbThreads)

plt.title("Time Performance Metrics [{}.c] vs. Number of Threads".format(program_name))
plt.xlabel('Number of Threads []')
plt.ylabel('Execution Time [{}]'.format(unity_time))
plt.ylim(0)
plt.legend()
plt.grid()
plt.savefig("graphs/png/" + csv_file_name + ".png")
plt.savefig("graphs/pdf/" + csv_file_name + ".pdf")
plt.show()