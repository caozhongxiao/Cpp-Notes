#include <iostream>
#include <algorithm>
using namespace std;
#include <vector>

//选择排序
template<class T>
void selectSort(T &arr){
	int len = arr.size();
	for(int i = 0; i < len-1; ++i){
		int min = i;
		for(int j = i+1; j < len; ++j){
			if(arr[j] < arr[min])
				min = j;
		}
		if(min != i)
			swap(arr[i], arr[min]);
	}
}

int main()
{
	vector<int> v = {9, 8, 4, 6, 7, 3, 5, 2, 1};
	selectSort(v);
	for(auto it = v.begin(); it != v.end(); ++it){
		cout << *it << " ";
	}

	return 0;
}