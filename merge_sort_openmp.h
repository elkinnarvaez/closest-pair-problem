#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
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

bool comp_x(const Point &p1, const Point &p2){
    return p1.x < p2.x;
}

bool comp_y(const Point &p1, const Point &p2){
    return p1.y < p2.y;
}

void merge_sort_comp_x(vector<Point>& v, int p, int q)	{
	if (p < q)	{
		if (q - p >= 32)	{
			int mid = p + ((q - p)>>1);
            #pragma omp taskgroup
            {
                #pragma omp task shared(v) untied if(q - p >= (1<<14))
                merge_sort_comp_x(v, p, mid);
                #pragma omp task shared(v) untied if(q - p >= (1<<14))
                merge_sort_comp_x(v, mid + 1, q);
                #pragma omp taskyield
            }
			inplace_merge(v.begin() + p, v.begin() + mid + 1, v.begin() + q + 1, comp_x);
		} else {
			sort(v.begin() + p, v.begin() + q + 1, comp_x);
		}
	}
}

void merge_sort_comp_y(vector<Point>& v, int p, int q)	{
	if (p < q)	{
		if (q - p >= 32)	{
			int mid = p + ((q - p)>>1);
            #pragma omp taskgroup
            {
                #pragma omp task shared(v) untied if(q - p >= (1<<14))
                merge_sort_comp_y(v, p, mid);
                #pragma omp task shared(v) untied if(q - p >= (1<<14))
                merge_sort_comp_y(v, mid + 1, q);
                #pragma omp taskyield
            }
			inplace_merge(v.begin() + p, v.begin() + mid + 1, v.begin() + q + 1, comp_y);
		} else {
			sort(v.begin() + p, v.begin() + q + 1, comp_y);
		}
	}
}

void print_point_vector(const vector<Point>& v, int N){
    for(int i = 0; i < N; i++){
        printf("%f %f\n", v[i].x, v[i].y);
    }
}

// int main(){
//     int N = 100;
//     vector<Point> a(N);
//     for(int i = 0; i < N; i++){
//         int x = (rand() % 100 + 1);
//         int y = (rand() % 100 + 1);
//         a[i] = Point(x, y);
//     }
//     print_point_vector(a, N);
//     printf("------------------------------------------\n");
//     #pragma omp parallel
//     #pragma omp single
//     merge_sort_comp_x(a, 0, N - 1);
//     print_point_vector(a, N);
//     return 0;
// }