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
data = data.values.transpose()

unity_time = "s"
if np.max(data) < 1:
    unity_time = "ms"
    data *= 1000

plt.figure()

box = plt.boxplot(data, vert=True, meanline=True, showmeans=True, patch_artist=True)

colors = ['lightblue', 'lightgreen', 'lightyellow', 'lightpink', 'lightgray']

for patch, color in zip(box['boxes'], colors):
    patch.set_facecolor(color)

plt.xticks(np.arange(1, len(nbThreads) + 1), nbThreads)

plt.title("Time Performance Metrics [{}.c] vs. Number of Threads".format(program_name))
plt.xlabel('Number of Threads []')
plt.ylabel('Execution Time [{}]'.format(unity_time))
plt.legend()
plt.grid()
plt.savefig("graphs/png/" + csv_file_name + ".png")
plt.savefig("graphs/pdf/" + csv_file_name + ".pdf")
plt.show()