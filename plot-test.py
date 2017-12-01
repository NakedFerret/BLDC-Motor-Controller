import matplotlib
matplotlib.use('WXAgg')
import matplotlib.pyplot as plt
import numpy as np

time, voltage = np.loadtxt('tmp-recorder-test', delimiter=',', unpack=True)

plt.plot(time, voltage)

plt.show()
