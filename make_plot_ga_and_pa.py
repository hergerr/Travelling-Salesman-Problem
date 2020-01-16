import matplotlib
import matplotlib.pyplot as plt
import numpy as np

names = []
results = []
expected = []

file_name = 'pa_data.txt'

with open(file_name) as file:
    next(file) # skip title line
    for line in file:
        splitted_line = line.split()
        names.append(splitted_line[0].replace(':', ''))
        results.append(int(splitted_line[1]))
        expected.append(int(splitted_line[2]))

for i in range(0, len(names)):
    print(f"{names[i]} & {expected[i]} & {results[i]} & {100*(results[i] - expected[i])/expected[i]:.2f}\\%\\\\" )
    print("\hline")
    
    
x = np.arange(len(names))  # the label locations
width = 0.35  # the width of the bars

fig, ax = plt.subplots()
rects1 = ax.bar(x - width/2, expected, width, label='Rozwiązanie optymalne')
rects2 = ax.bar(x + width/2, results, width, label='Otrzymane rozwiązanie')

ax.set_ylabel('Koszt')
ax.set_title('Koszty optymalne i otrzymane rozwiązania')
ax.set_xticks(x)
ax.set_xticklabels(names)
ax.legend()

def autolabel(rects):
    """Attach a text label above each bar in *rects*, displaying its height."""
    for rect in rects:
        height = rect.get_height()
        ax.annotate('{}'.format(height),
                    xy=(rect.get_x() + rect.get_width() / 2, height),
                    xytext=(0, 3),  # 3 points vertical offset
                    textcoords="offset points",
                    ha='center', va='bottom')

autolabel(rects1)
autolabel(rects2)

fig.tight_layout(pad=3.5)

plt.show()