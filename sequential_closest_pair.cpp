#include <bits/stdc++.h>
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

double closest_pair_problem_2d(const vector<Point> &coordinates, const int &p, const int &q){
    double ans;
    
    if((q - p) <= 3){
        ans = closest_pair_problem_naive(coordinates, p, q);
    }
    else{
        int mid = p + ((q - p)>>1);
        double median = coordinates[mid].x;
        double ansL = closest_pair_problem_2d(coordinates, p, mid);
        double ansR = closest_pair_problem_2d(coordinates, mid, q);
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

double solve(vector<Point> coordinates, const int &n){
    double ans;
    sort(coordinates.begin(), coordinates.end(), comp_x);
    ans = closest_pair_problem_2d(coordinates, 0, n);
    // if(ans >= 10000){
    //     ans = -1.0;
    // }
    return ans;
}

int main(){
    int n;
    double x, y;
    while(cin >> n){
        if(n == 0) continue;
        vector<Point> coordinates(n);
        for(int i = 0; i < n; i++){
            cin >> x >> y;
            coordinates[i] = Point(x, y);
        }
        double s;
        double start,stop;
        int num_iter = 5;
        double sum_time = 0;
        double running_times[num_iter];
        for(int i = 0; i < num_iter; i++){
            start = omp_get_wtime();
            s = solve(coordinates, n);
            stop = omp_get_wtime();
            // printf("Time: %f\n", stop - start);
            sum_time = sum_time + (stop - start);
            running_times[i] = (stop - start);
        }
        // printf("Time for n = %d is %f\n", n, sum_time/num_iter);
        printf("%d %f %d", n, sum_time/num_iter, num_iter);
        for(int i = 0; i < num_iter; i++){
            printf(" %f", running_times[i]);
        }
        printf("\n");
        // if(s == -1.0){
        //     printf("INFINITY\n");
        // }
        // else{
        //     printf("%.4f\n", s);
        // }
    }
    return 0;
}