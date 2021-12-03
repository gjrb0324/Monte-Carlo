import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(projection='3d')

data = np.loadtxt('./output.csv', unpack=True, delimiter=',', skiprows=1)
X = data[0]
Y = data[1]
Z  =data[2]

subplot.scatter(X,Y,Z)

subplot.set_xlabel('E')
subplot.set_ylabel('M')
subplot.set_zlable('g')
plt.suptitle('Result',fontsize=16)
plt.show()
