#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void merge(vector<int> &arr, int l, int mid, int r){
	int i = l, j = mid+1, k = 0;
	int *tmp = new int[r-l+1];
	while(i <= mid && j <= r){
		if(arr[i] < arr[j])
			tmp[k++] = arr[i++];
		else
			tmp[k++] = arr[j++];
	}
	while(i <= mid) 
		tmp[k++] = arr[i++];
	while(j <= r) 
		tmp[k++] = arr[j++];
	for(int i = 0; i < r-l+1; ++i) 
		arr[i+l] = tmp[i];
	delete[] tmp;
}

//1. 递归写法
void mergeSort(vector<int> &arr, int l, int r){
	if(l < r){
		int mid = (l + r) >> 1;
		mergeSort(arr, l, mid);
		mergeSort(arr, mid+1, r);
		merge(arr, l, mid, r);
	}
}

//2. 非递归写法
void mergeSort(vector<int> &arr){
    int n = arr.size();
    for(int size = 1; size < n; size <<= 1){
        //low+size=mid+1，为第二个分区第一个元素，它 < n，确保最后一次合并有2个区间
        for(int low = 0; low+size < n; low += 2*size){
            int mid = low + size - 1; //mid：第一有序区最后一个元素下标
            int high = low + 2*size - 1;//high：第二有序区最后一个元素下标
            if(high > n-1) high = n-1;
            merge(arr, low, mid, high);
        }
    }
}

int main()
{
	vector<int> v = {9, 8, 4, 6, 7, 3, 5, 2, 1};
	mergeSort(v, 0, v.size()-1);//递归
	mergeSort(v);//非递归
	for(auto it = v.begin(); it != v.end(); ++it){
		cout << *it << " ";
	}
	return 0;
}