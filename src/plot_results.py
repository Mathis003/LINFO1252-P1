from matplotlib import pyplot as plt
import pandas as pd

data = pd.read_csv("csv_files/perfs_philosopher.csv")
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
plt.savefig("graphs/png/perfs_philosopher.png")
plt.savefig("graphs/pdf/perfs_philosopher.pdf")
plt.show()


data = pd.read_csv("csv_files/perfs_producer_consumer.csv")
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
plt.savefig("graphs/png/perfs_producer_consumer.png")
plt.savefig("graphs/pdf/perfs_producer_consumer.pdf")
plt.show()



data = pd.read_csv("csv_files/reader_writer.csv")
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
plt.savefig("graphs/png/reader_writer.png")
plt.savefig("graphs/pdf/reader_writer.pdf")
plt.show()