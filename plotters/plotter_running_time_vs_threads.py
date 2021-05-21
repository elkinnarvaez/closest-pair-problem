from sys import stdin
import matplotlib
import matplotlib.pyplot as plt

def main():
    f1 = open("data/running_time_vs_number_of_threads.txt", "r")
    lines1 = f1.readlines()
    f1.close()
    x_axis1 = list()
    y_axis1 = list()
    for line in lines1:
        if len(line) > 0:
            l = line.strip().split()
            p = int(l[0])
            t = float(l[1])
            x_axis1.append(p)
            y_axis1.append(t)

    fig1, ax1 = plt.subplots()
    ax1.plot(x_axis1, y_axis1, c='b')
    ax1.scatter(x_axis1, y_axis1, c='b')
    ax1.set_title(f'Running time as the number of threads increases with a fixed data size of 500K')
    ax1.set_xlabel(f'Number of processors')
    ax1.set_ylabel(f'Running time')
    ax1.grid(True)
    ax1.legend()

    plt.show()

    return 0

if __name__ == '__main__':
    main()