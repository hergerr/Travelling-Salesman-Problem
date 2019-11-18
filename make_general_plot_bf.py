import re
import matplotlib.pyplot as plt
import numpy


for i in (10, 11, 12, 13):
    used_mem_list = []
    with open(f'data{i}_bf.txt') as file:
        for line in file:
            used_mem_list.append(int(re.sub(' +',' ',line).split(' ')[2]))

    plt.plot(range(0, len(used_mem_list)), used_mem_list, label=f'data{i}')
    plt.title('Brute Force - porównanie')
    plt.xlabel('Numer próbki')
    plt.ylabel('Ilość zajętej pamięci w kB')

plt.legend()
plt.savefig(f'Wykres_ogólny_dla_bf.png')

