#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template<class T>
void insertSort(T &arr){
	int len = arr.size();
	for(int i = 1; i < len; ++i){
		auto e = arr[i];
		int j;
		for(j = i; j > 0 && arr[j-1] > e; --j){
			arr[j] = arr[j-1];
		}
		arr[j] = e;
	}
}

int main()
{
	vector<int> v = {9, 8, 4, 6, 7, 3, 5, 2, 1};
	insertSort(v);
	for(auto it = v.begin(); it != v.end(); ++it){
		cout << *it << " ";
	}

	return 0;
}