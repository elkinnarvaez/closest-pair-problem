# Closest Pair Problem

1. Execution with OpenMP
    * g++ sequential_closest_pair.cpp -fopenmp -o sequential_closest_pair.out
    * g++ parallel_closest_pair_openmp.cpp -fopenmp -o parallel_closest_pair_openmp.out
    * ./sequential_closest_pair.out < input.txt > output.txt
    * ./parallel_closest_pair_openmp.out < input.txt > output.txt
2. Execution with MPI
    * mpiCC parallel_closest_pair_mpi.cpp -o parallel_closest_pair_mpi.out
    * mpirun -n 2 ./parallel_closest_pair_mpi.out > output.txt
3. Execution with OpenMP and MPI
    * mpiCC parallel_closest_pair_mpi.cpp -fopenmp -o parallel_closest_pair_mpi.out
    * mpirun -n 2 ./parallel_closest_pair_mpi.out > output.txt
4. Gprof execution
    * g++ sequential_closest_pair.cpp -fopenmp -o sequential_closest_pair.out -pg
    * time ./sequential_closest_pair.out < input.txt
    * gprof sequential_closest_pair.out gmon.out > analysis.txt
5. OpenMP environment variables commands
    * export OMP_NUM_THREADS=8
6. Execution with MPI - MPI examples
    * mpiCC hello_world.cpp -o hello_world.out | mpicxx hello_world.cpp -o hello_world.out
    * mpirun -n 4 ./hello_world.out | mpiexec -n 4 ./hello_world.out
7. Coderrect
    * coderrect -t mpiCC -fopenmp -g parallel_closest_pair_mpi.cpp