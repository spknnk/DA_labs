import matplotlib.pyplot as plt
import numpy as np

n_list = [1, 2, 3, 4, 5, 6, 7, 8]
a_list = [2804, 2530, 6313, 1682, 3310, 3608, 2647, 2278]
m_list = [2158, 939, 3512, 1179, 1685, 2298, 1559, 1310]


plt.plot(n_list, a_list, color='b', marker='.', label='std::map')
plt.plot(n_list, m_list, color='r', marker='.', label='RBtree')

plt.legend(loc=2, borderaxespad=1)

plt.xlabel('Test num')
plt.ylabel('Time(μs)')
plt.title('%%time')
# plt.grid(True)
plt.savefig("time.png")
plt.show()
