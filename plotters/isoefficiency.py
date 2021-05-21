from sys import stdin
import matplotlib
import matplotlib.pyplot as plt

def main():
    f1 = open("data/running_time_iso_sequential_100000.txt", "r")
    f2 = open("data/running_time_iso_parallel_100000.txt", "r")
    f3 = open("data/running_time_iso_sequential_300000.txt", "r")
    f4 = open("data/running_time_iso_parallel_300000.txt", "r")
    f5 = open("data/running_time_iso_sequential_500000.txt", "r")
    f6 = open("data/running_time_iso_parallel_500000.txt", "r")
    lines1 = f1.readlines()
    lines2 = f2.readlines()
    lines3 = f3.readlines()
    lines4 = f4.readlines()
    lines5 = f5.readlines()
    lines6 = f6.readlines()
    f1.close()
    f2.close()
    f3.close()
    f4.close()
    f5.close()
    f6.close()
    x_axis1, x_axis2, x_axis3, x_axis4, x_axis5, x_axis6 = list(), list(), list(), list(), list(), list()
    y_axis1, y_axis2, y_axis3, y_axis4, y_axis5, y_axis6 = list(), list(), list(), list(), list(), list()
    for line in lines1:
        if len(line) > 0:
            l = line.strip().split()
            p = int(l[0])
            t = float(l[1])
            x_axis1.append(p)
            y_axis1.append(t)
    for line in lines2:
        if len(line) > 0:
            l = line.strip().split()
            p = int(l[0])
            t = float(l[1])
            x_axis2.append(p)
            y_axis2.append(t)
    for line in lines3:
        if len(line) > 0:
            l = line.strip().split()
            p = int(l[0])
            t = float(l[1])
            x_axis3.append(p)
            y_axis3.append(t)
    for line in lines4:
        if len(line) > 0:
            l = line.strip().split()
            p = int(l[0])
            t = float(l[1])
            x_axis4.append(p)
            y_axis4.append(t)
    for line in lines5:
        if len(line) > 0:
            l = line.strip().split()
            p = int(l[0])
            t = float(l[1])
            x_axis5.append(p)
            y_axis5.append(t)
    for line in lines6:
        if len(line) > 0:
            l = line.strip().split()
            p = int(l[0])
            t = float(l[1])
            x_axis6.append(p)
            y_axis6.append(t)
    efficiency1 = [(y_axis1[i]/y_axis2[i])/x_axis1[i] for i in range(len(y_axis1))]
    efficiency2 = [(y_axis3[i]/y_axis4[i])/x_axis3[i] for i in range(len(y_axis3))]
    efficiency3 = [(y_axis5[i]/y_axis6[i])/x_axis5[i] for i in range(len(y_axis5))]
    fig1, ax1 = plt.subplots()
    ax1.plot(x_axis1, efficiency1, c='b', label='100K array values')
    ax1.scatter(x_axis1, efficiency1, c='b')
    ax1.plot(x_axis1, efficiency2, c='g', label='300K array values')
    ax1.scatter(x_axis1, efficiency2, c='g')
    ax1.plot(x_axis1, efficiency3, c='r', label='500K array values')
    ax1.scatter(x_axis1, efficiency3, c='r')
    ax1.set_title(f'Isoefficiency')
    ax1.set_xlabel(f'Number of processors')
    ax1.set_ylabel(f'Efficiency')
    ax1.grid(True)
    ax1.legend()

    plt.show()

    return 0

if __name__ == '__main__':
    main()