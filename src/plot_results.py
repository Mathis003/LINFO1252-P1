from matplotlib import pyplot as plt
import pandas as pd
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

data = pd.read_csv(csv_file)
nbThreads = data['NbThreads']
data = data.drop(columns="NbThreads")

medians = []
means = []
stds = []

for index, row in data.iterrows():
    medians.append(row.median())
    means.append(row.mean())
    stds.append(row.std())

plt.figure()
plt.plot(nbThreads, means, marker='o', markersize=6, color='blue', linestyle='-', label='Mean')
plt.scatter(nbThreads, medians, color='green', label='Median', s=40)
plt.errorbar(nbThreads, medians, yerr=stds, fmt='o', markersize=5, color='red', label='Std Dev')
plt.title('Time Performance Metrics vs. Number of Threads')
plt.xlabel('Number of Threads []')
plt.ylabel('Execution Time [sec]')
plt.legend()
plt.grid()
csv_file_name = os.path.splitext(os.path.basename(csv_file))[0]
plt.savefig("graphs/png/" + csv_file_name + ".png")
plt.savefig("graphs/pdf/" + csv_file_name + ".pdf")
# plt.show()