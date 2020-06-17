#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//冒泡排序
template<class T>
void bubbleSort(T &arr){
	int len = arr.size();
	for(int i = 0; i < len-1; ++i){
		bool isSwap = false;
		for(int j = 0; j < len-i-1; ++j){
			if(arr[j] > arr[j+1]){
				swap(arr[j], arr[j+1]);
				isSwap = true;
			}
		}
		if(!isSwap) return;
	}
}

int main()
{
	vector<int> v = {9, 8, 4, 6, 7, 3, 5, 2, 1};
	bubbleSort(v);
	for(auto it = v.begin(); it != v.end(); ++it){
		cout << *it << " ";
	}

	return 0;
}