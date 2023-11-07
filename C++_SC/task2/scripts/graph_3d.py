import pandas as pd
import sys
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

data = pd.read_csv(sys.argv[1])

sample_data = data.iloc[::200, :]

i = sample_data['i']
j = sample_data['j']
k = sample_data['k']
value = sample_data['value']

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

scatter = ax.scatter(i, j, k, c=value, cmap='viridis', vmin=value.min(), vmax=value.max())

ax.set_xlabel('i')
ax.set_ylabel('j')
ax.set_zlabel('k')

fig.colorbar(scatter)

# plt.show()
plt.savefig(sys.argv[2])
