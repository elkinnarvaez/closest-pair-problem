#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace std::chrono;

void mergeSortRecursive(vector<double>& v, unsigned long left, unsigned long right)	{
	if (left < right)	{
		if (right-left >= 32)	{
			unsigned long mid = (left+right)/2;
			mergeSortRecursive(v, left, mid);
			mergeSortRecursive(v, mid+1, right);
			inplace_merge(v.begin()+left, v.begin()+mid+1, v.begin()+right+1);
		} else {
			sort(v.begin()+left, v.begin()+right+1);
		}
	}
}

void mergeSort(vector<double>& v)	{
	mergeSortRecursive(v, 0, v.size()-1);
}

int main()	{
	unsigned long n = 0;
	cout<<"Number of elements to sort: ";
	cin>>n;
	if (n <= 0)	{
		cerr<<"Invalid number of elements!"<<endl;
		return 1;
	}

	random_device rd;
	default_random_engine gen(rd());
	uniform_real_distribution<double> normVals(0.0, 1.0);
	// Generate data to sort...
	vector<double> toSortRef, toSort;
	for (unsigned long i = 0; i < n; ++i)
		toSort.push_back(normVals(gen));

	// Benchmark the sorting algorithms.
	toSortRef = toSort;
	high_resolution_clock::time_point start = high_resolution_clock::now();
	sort(toSortRef.begin(), toSortRef.end());
	high_resolution_clock::time_point mid = high_resolution_clock::now();
	mergeSort(toSort);
	high_resolution_clock::time_point end = high_resolution_clock::now();
	assert(is_sorted(toSort.cbegin(), toSort.cend()) && "Invalid sorting algorithm!");

	// Print the results...
	double stlRuntime = duration_cast<duration<double>>(mid-start).count();
	double mergeRuntime = duration_cast<duration<double>>(end-mid).count();

	cout<<"STL sort: "<<stlRuntime<<" s"<<endl;
	cout<<"Merge sort: "<<mergeRuntime<<" s"<<endl;

	return 0;
}

