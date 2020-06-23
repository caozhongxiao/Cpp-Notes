#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//希尔排序
void shellSort(vector<int> &arr){
	int len = arr.size();
	int gap = len/2;
	while(gap){
		for(int i = gap; i < len; ++i){
			for(int j = i-gap; j >= 0; j -= gap){
				if(arr[j] > arr[j+gap])
					swap(arr[j], arr[j+gap]);
			}
		}
		gap = gap/2;
	}
}

int main()
{
	vector<int> v = {9, 8, 4, 6, 7, 3, 5, 2, 1};
	shellSort(v);
	for(auto it = v.begin(); it != v.end(); ++it){
		cout << *it << " ";
	}
	return 0;
}