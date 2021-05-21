#include <bits/stdc++.h>
#include <mpi.h>
#include <omp.h>

using namespace std;

#define INF 99999999

class Point{
    public:
        double x, y;
        Point();
        Point(double, double);
};

Point::Point(){}

Point::Point(double x, double y){
    this->x = x;
    this->y = y;
}

vector<double> tokenizer(string s){
    vector<double> ans;
    stringstream ss(s);
    string word;
    while(ss >> word){
        ans.push_back(stod(word));
    }
    return ans;
}

double distance(const double &x1, const double &y1, const double &x2, const double &y2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

bool comp_x(const Point &p1, const Point &p2){
    return p1.x < p2.x;
}

bool comp_y(const Point &p1, const Point &p2){
    return p1.y < p2.y;
}

double closest_pair_problem_naive(const vector<Point> &coordinates, const int &p, const int &q){
    double ans = INF;
    for(int i = p; i < q - 1; i++){
        Point p1 = coordinates[i];
        for(int j = i + 1; j < q; j++){
            Point p2 = coordinates[j];
            double d = distance(p1.x, p1.y, p2.x, p2.y);
            if(d < ans){
                ans = d;
            }
        }
    }
    return ans;
}

double closest_pair_problem_2d_openmp(const vector<Point> &coordinates, const int &p, const int &q){
    double ans;
   
    if((q - p) <= 3){
        ans = closest_pair_problem_naive(coordinates, p, q);
    }
    else{
        int mid = p + ((q - p)>>1);
        double median = coordinates[mid].x;
        double ansL, ansR;
        #pragma omp parallel sections
        {
            #pragma omp section
                ansL = closest_pair_problem_2d_openmp(coordinates, p, mid);
            #pragma omp section
                ansR = closest_pair_problem_2d_openmp(coordinates, mid, q);
        }
        ans = min(ansL, ansR);
        vector<Point> strip;
        for(int i = p; i < q; i++){
            if(abs(coordinates[i].x - median) < ans){
                strip.push_back(coordinates[i]);
            }
        }
        sort(strip.begin(), strip.end(), comp_y);
        for(int i = 0; i < strip.size(); i++){
            for(int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < ans; j++){
                ans = min(ans, distance(strip[i].x, strip[i].y, strip[j].x, strip[j].y));
            }
        }
    }

    return ans;
}

double closest_pair_problem_2d_mpi(const vector<Point> &coordinates, const int &p, const int &q){
    double ans = 0.0;
    
    if((q - p) <= 3){
        ans = closest_pair_problem_naive(coordinates, p, q);
    }
    else{
        int mid = p + ((q - p)>>1);
        double median = coordinates[mid].x;
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        if(rank == 0){
            double ansL = closest_pair_problem_2d_openmp(coordinates, p, mid);
            double ansR;
            MPI_Recv(&ansR, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            ans = min(ansL, ansR);
            vector<Point> strip;
            for(int i = p; i < q; i++){
                if(abs(coordinates[i].x - median) < ans){
                    strip.push_back(coordinates[i]);
                }
            }
            sort(strip.begin(), strip.end(), comp_y);
            for(int i = 0; i < strip.size(); i++){
                for(int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < ans; j++){
                    ans = min(ans, distance(strip[i].x, strip[i].y, strip[j].x, strip[j].y));
                }
            }
        }
        else{
            double ansR = closest_pair_problem_2d_openmp(coordinates, mid, q);
            MPI_Send(&ansR, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
    }

    return ans;
}

double solve(vector<Point> coordinates, const int &n){
    double ans;
    sort(coordinates.begin(), coordinates.end(), comp_x);
    ans = closest_pair_problem_2d_mpi(coordinates, 0, n);
    // if(ans >= 10000){
    //     ans = -1.0;
    // }
    return ans;
}

int main(int argc, char* argv[]){
    int rank;
    char buff[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int n;
    double x, y;
    ifstream newfile("input.txt");
    string line;
    while(true){
        if(rank == 0){
            getline(newfile, line);
            strcpy(buff, line.c_str());
            MPI_Send(buff, 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
            if(line.size() == 0){
                break;
            }
        }
        else{
            MPI_Recv(buff, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            line = "";
            line += buff;
            if(line.size() == 0){
                break;
            }
        }
        n = stoi(line);
        // if(rank == 0){
        //     cout << n << endl;
        // }
        if(n == 0) break;
        vector<Point> coordinates(n);
        for(int i = 0; i < n; i++){
            if(rank == 0){
                getline(newfile, line);
                strcpy(buff, line.c_str());
                MPI_Send(buff, 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
            }
            else{
                MPI_Recv(buff, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                line = "";
                line += buff;
            }
            vector<double> split_line = tokenizer(line);
            // if(rank == 0){
            //     cout << split_line[0] << " " << split_line[1] << endl;
            // }
            coordinates[i] = Point(split_line[0], split_line[1]);
        }
        double s;
        double start, stop;
        int num_iter = 5;
        double sum_time = 0;
        double running_times[num_iter];
        for(int i = 0; i < num_iter; i++){
            start = MPI_Wtime();
            s = solve(coordinates, n);
            stop = MPI_Wtime();
            // printf("Time: %f\n", stop - start);
            sum_time = sum_time + (stop - start);
            running_times[i] = (stop - start);
        }
        if(rank == 0){
            // printf("Time for n = %d is %f\n", n, sum_time/num_iter);
            printf("%d %f %d", n, sum_time/num_iter, num_iter);
            for(int i = 0; i < num_iter; i++){
                printf(" %f", running_times[i]);
            }
            printf("\n");
        }
        // if(rank == 0){
        //     if(s == -1.0){
        //         printf("INFINITY\n");
        //     }
        //     else{
        //         printf("%.4f\n", s);
        //     }
        // }
    }
    newfile.close();
    MPI_Finalize();
    return 0;
}

// int main(int argc, char* argv[]){
//     MPI_Init(&argc, &argv);
//     int n, rank;
//     double x, y;
//     ifstream newfile("input.txt");
//     string line;
//     while(getline(newfile, line)){
//         n = stoi(line);
//         // cout << n << endl;
//         if(n == 0) continue;
//         vector<Point> coordinates(n);
//         for(int i = 0; i < n; i++){
//             getline(newfile, line);
//             vector<double> split_line = tokenizer(line);
//             // cout << split_line[0] << " " << split_line[1] << endl;
//             coordinates[i] = Point(split_line[0], split_line[1]);
//         }
//         double s;
//         double start, stop;
//         int num_iter = 1;
//         double sum_time = 0;
//         double running_times[num_iter];
//         for(int i = 0; i < num_iter; i++){
//             start = MPI_Wtime();
//             s = solve(coordinates, n);
//             stop = MPI_Wtime();
//             // printf("Time: %f\n", stop - start);
//             sum_time = sum_time + (stop - start);
//             running_times[i] = (stop - start);
//         }
//         // printf("Time for n = %d is %f\n", n, sum_time/num_iter);
//         // printf("%d %f %d", n, sum_time/num_iter, num_iter);
//         // for(int i = 0; i < num_iter; i++){
//         //     printf(" %f", running_times[i]);
//         // }
//         // printf("\n");
//         MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//         if(rank == 0){
//             if(s == -1.0){
//                 printf("INFINITY\n");
//             }
//             else{
//                 printf("%.4f\n", s);
//             }
//         }
//     }
//     newfile.close();
//     MPI_Finalize();
//     return 0;
// }