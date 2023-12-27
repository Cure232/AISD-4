import matplotlib.pyplot as plt
import numpy as np

def out(path):
    #Z - копирования, Y - сравнения
    x1, y1, z1 = np.loadtxt(f"rand_data_{path}_sort.txt", unpack=True)
    # Построение графика

    plt.plot(x1, y1, marker='o', linestyle=':', color="#000000")
    plt.plot(x1, z1, marker='o', linestyle=':', color="#000000")

    x2, y2, z2 = np.loadtxt(f"sorted_{path}.txt", unpack=True)
    # Построение графика

    plt.plot(x2, y2, marker='o', linestyle=':')
    plt.plot(x2, z2, marker='o', linestyle=':')

    x3, y3, z3 = np.loadtxt(f"unsorted_{path}.txt", unpack=True)
    # Построение графика

    plt.plot(x3, y3, marker='o', linestyle=':')
    plt.plot(x3, z3, marker='o', linestyle=':')

    plt.title(f'Scatter Plot of Points ({path})')

    plt.xlabel('Arr size')
    plt.ylabel('Interaction count')

    plt.show()


out('insert')
out('shaker')
out('comb')