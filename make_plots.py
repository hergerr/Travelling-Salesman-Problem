import re
import matplotlib.pyplot as plt
import numpy


used_mem_list = []

with open('data21.txt') as file:
    for line in file:
        used_mem_list.append(int(re.sub(' +',' ',line).split(' ')[2]))

plt.plot(range(0, len(used_mem_list)), used_mem_list, label='data21')
plt.title('Zużycie pamięci dla algorytmu dynamicznego')
plt.xlabel('Numer próbki')
plt.ylabel('Ilość zajętej pamięci')
plt.legend()
plt.show()
