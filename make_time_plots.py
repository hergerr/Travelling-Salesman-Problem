import re
import matplotlib.pyplot as plt



plt.clf()
time_list = []
with open(f'times_bf.txt') as file:
    for line in file:
       time_list.append(float(line))

plt.xticks([10,11,12])
plt.plot([10,11,12], time_list, label=f'Brute force')
plt.title(f'Brute force ')
plt.xlabel('Rząd grafu')
plt.ylabel('Czas w s')
plt.savefig(f'Wykres_czasowy_bf.png', bbox_inches='tight')


plt.clf()
time_list = []
with open(f'times_dp.txt') as file:
    for line in file:
       time_list.append(float(line))


plt.plot([10,11,12,13,14,15,16,17,18,21,24,26], time_list, label=f'Programowanie dynamiczne')
plt.title(f'Programowanie dynamiczne ')
plt.xlabel('Rząd grafu')
plt.ylabel('Czas w s')
plt.savefig(f'Wykres_czasowy_dp.png', bbox_inches='tight')
