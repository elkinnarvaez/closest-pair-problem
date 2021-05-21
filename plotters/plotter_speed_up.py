from sys import stdin
import matplotlib
import matplotlib.pyplot as plt

def main():
    f1 = open("data/running_time_sequential.txt", "r")
    f2 = open("data/running_time_parallel_openmp_6_omp_threads.txt", "r")
    f3 = open("data/running_time_parallel_openmp_and_mpi_2_omp_threads.txt", "r")
    f4 = open("data/running_time_parallel_openmp_and_mpi_4_omp_threads.txt", "r")
    f5 = open("data/running_time_parallel_openmp_and_mpi_6_omp_threads.txt", "r")
    f6 = open("data/running_time_parallel_openmp_and_mpi_8_omp_threads.txt", "r")
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
            n = int(l[0])
            if(n%50000 == 0):
                t = float(l[1])
                x_axis1.append(n)
                y_axis1.append(t)
    for line in lines2:
        if len(line) > 0:
            l = line.strip().split()
            n = int(l[0])
            if(n%50000 == 0):
                t = float(l[1])
                x_axis2.append(n)
                y_axis2.append(t)
    for line in lines3:
        if len(line) > 0:
            l = line.strip().split()
            n = int(l[0])
            if(n%50000 == 0):
                t = float(l[1])
                x_axis3.append(n)
                y_axis3.append(t)
    for line in lines4:
        if len(line) > 0:
            l = line.strip().split()
            n = int(l[0])
            if(n%50000 == 0):
                t = float(l[1])
                x_axis4.append(n)
                y_axis4.append(t)
    for line in lines5:
        if len(line) > 0:
            l = line.strip().split()
            n = int(l[0])
            if(n%50000 == 0):
                t = float(l[1])
                x_axis5.append(n)
                y_axis5.append(t)
    for line in lines6:
        if len(line) > 0:
            l = line.strip().split()
            n = int(l[0])
            if(n%50000 == 0):
                t = float(l[1])
                x_axis6.append(n)
                y_axis6.append(t)
    speed_up1 = [y_axis1[i]/y_axis2[i] for i in range(len(y_axis1))]
    speed_up2 = [y_axis1[i]/y_axis3[i] for i in range(len(y_axis1))]
    speed_up3 = [y_axis1[i]/y_axis4[i] for i in range(len(y_axis1))]
    speed_up4 = [y_axis1[i]/y_axis5[i] for i in range(len(y_axis1))]
    speed_up5 = [y_axis1[i]/y_axis6[i] for i in range(len(y_axis1))]

    fig1, ax1 = plt.subplots()
    ax1.plot(x_axis1, y_axis1, c='r')
    ax1.scatter(x_axis1, y_axis1, c='r', s=25)
    ax1.set_title(f'Running time sequential algorithm')
    ax1.set_xlabel(f'N')
    ax1.set_ylabel(f'Time (seconds)')
    ax1.grid(True)

    fig2, ax2 = plt.subplots()
    ax2.plot(x_axis2, y_axis2, c='r')
    ax2.scatter(x_axis2, y_axis2, c='r', s=25)
    ax2.set_title(f'Running time parallel algorithm using OpenMP with 6 OMP threads')
    ax2.set_xlabel(f'N')
    ax2.set_ylabel(f'Time (seconds)')
    ax2.grid(True)

    fig3, ax3 = plt.subplots()
    ax3.plot(x_axis3, y_axis3, c='r')
    ax3.scatter(x_axis3, y_axis3, c='r', s=25)
    ax3.set_title(f'Running time parallel algorithm using OpenMP and MPI with 2 OMP threads')
    ax3.set_xlabel(f'N')
    ax3.set_ylabel(f'Time (seconds)')
    ax3.grid(True)

    fig4, ax4 = plt.subplots()
    ax4.plot(x_axis4, y_axis4, c='r')
    ax4.scatter(x_axis4, y_axis4, c='r', s=25)
    ax4.set_title(f'Running time parallel algorithm using OpenMP and MPI with 4 OMP threads')
    ax4.set_xlabel(f'N')
    ax4.set_ylabel(f'Time (seconds)')
    ax4.grid(True)

    fig5, ax5 = plt.subplots()
    ax5.plot(x_axis5, y_axis5, c='r')
    ax5.scatter(x_axis5, y_axis5, c='r', s=25)
    ax5.set_title(f'Running time parallel algorithm using OpenMP and MPI with 6 OMP threads')
    ax5.set_xlabel(f'N')
    ax5.set_ylabel(f'Time (seconds)')
    ax5.grid(True)

    fig6, ax6 = plt.subplots()
    ax6.plot(x_axis6, y_axis6, c='r')
    ax6.scatter(x_axis6, y_axis6, c='r', s=25)
    ax6.set_title(f'Running time parallel algorithm using OpenMP and MPI with 8 OMP threads')
    ax6.set_xlabel(f'N')
    ax6.set_ylabel(f'Time (seconds)')
    ax6.grid(True)

    fig7, ax7 = plt.subplots()
    ax7.plot(x_axis1, speed_up1, c='b', label = "OpenMP with 6 OMP threads")
    ax7.scatter(x_axis1, speed_up1, c='b')
    ax7.plot(x_axis1, speed_up2, c='r', label = "OpenMP and MPI with 2 OMP threads")
    ax7.scatter(x_axis1, speed_up2, c='r')
    ax7.plot(x_axis1, speed_up3, c='g', label = "OpenMP and MPI with 4 OMP threads")
    ax7.scatter(x_axis1, speed_up3, c='g')
    ax7.plot(x_axis1, speed_up4, c='y', label = "OpenMP and MPI with 6 OMP threads")
    ax7.scatter(x_axis1, speed_up4, c='y')
    ax7.plot(x_axis1, speed_up5, c='c', label = "OpenMP and MPI with 8 OMP threads")
    ax7.scatter(x_axis1, speed_up5, c='c')
    ax7.set_title(f'Speed up')
    ax7.set_xlabel(f'N')
    ax7.set_ylabel(f'Speed up')
    ax7.grid(True)
    ax7.legend()

    plt.show()

    return 0

if __name__ == '__main__':
    main()