import json
import matplotlib.pyplot as plt
import sys


# Load JSON data
data = json.load(open(sys.argv[1]))
# Separate data based on L value
data_L1 = [entry for entry in data if entry["L"] == 1.0]
data_LPi = [entry for entry in data if entry["L"] == 3.14159265]

# Extract data for plotting
threads_L1 = [entry["threads"] for entry in data_L1]
times_L1 = [entry["time"] for entry in data_L1]

threads_LPi = [entry["threads"] for entry in data_LPi]
times_LPi = [entry["time"] for entry in data_LPi]

# Create line charts
plt.plot(threads_L1, times_L1, marker='o', label='L=1.0')
plt.plot(threads_LPi, times_LPi, marker='o', label='L=3.14159265')

# Add labels and title
plt.xlabel("Number of Threads")
plt.ylabel("Time (s)")
plt.title("Execution Time vs. Number of Threads")

# Add legend
plt.legend()

# Display the plot
# plt.show()
plt.savefig(sys.argv[2])