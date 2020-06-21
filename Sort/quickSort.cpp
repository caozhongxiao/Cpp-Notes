#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int partition(vector<int> &arr, int low, int high){
	int i = low, j = high;
	int v = arr[low];
	while(i < j){
		while(i < j && arr[j] >= v)
			--j;
		arr[i] = arr[j];
		while(i < j && arr[i] <= v)
			++i;
		arr[j] = arr[i];
	}
	arr[i] = v;
	return i;
}

void quickSort(vector<int> &arr, int low, int high){
	if(low < high){
		int p = partition(arr, low, high);
		quickSort(arr, low, p-1);
		quickSort(arr, p+1, high);
	}
}

int main()
{
	vector<int> v = {9, 8, 4, 6, 7, 3, 5, 2, 1};
	quickSort(v, 0, v.size()-1);
	for(auto it = v.begin(); it != v.end(); ++it){
		cout << *it << " ";
	}
	return 0;
}