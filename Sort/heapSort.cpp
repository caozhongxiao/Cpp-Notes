#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//1. 递归建堆
void heapify(vector<int> &arr, int idx, int len){
	int p = idx;
	int l = 2*p + 1;
	int r = 2*p + 2;
	if(l < len && arr[l] > arr[p])
		p = l;
	if(r < len && arr[r] > arr[p])
		p = r;
	if(p != idx){
		swap(arr[idx], arr[p]);
		heapify(arr, p, len);
	}
}

//2. 非递归建堆
void heapify(vector<int> &arr, int idx, int len){
	int p = idx;
	int l = 2*p + 1;
	int r = 2*p + 2;
	while(l < len){
		if(arr[l] > arr[p])
			p = l;
		if(r < len && arr[r] > arr[p])
			p = r;
		if(p != idx)
			swap(arr[idx], arr[p]);
		else
			break;
		idx = p;
		l = 2*idx + 1;
		r = 2*idx + 2;
	}
}

//堆排序
void heapSort(vector<int> &arr){
	int len = arr.size();
	for(int i = len/2-1; i >= 0; --i){
		heapify(arr, i, len);
	}
	
	for(int i = len-1; i > 0; --i){
		swap(arr[0], arr[i]);
		heapify(arr, 0, i);
	}
}

int main()
{
	vector<int> v = {9, 8, 4, 6, 7, 3, 5, 2, 1};
	heapSort(v);
	for(auto it = v.begin(); it != v.end(); ++it){
		cout << *it << " ";
	}

	return 0;
}


// //参考链接：https://www.geeksforgeeks.org/heap-sort/
// // C++ program for implementation of Heap Sort 
// // arr[0]~arr[n-1]
// // To heapify a subtree rooted with node i which is an index in arr[]. n is size of heap 
// void heapify(int arr[], int n, int i) 
// { 
//     int largest = i; // Initialize largest as root 
//     int l = 2*i + 1; // left = 2*i + 1 
//     int r = 2*i + 2; // right = 2*i + 2 
   
//     if (l < n && arr[l] > arr[largest]) // If left child is larger than root
//         largest = l; 
  
//     if (r < n && arr[r] > arr[largest]) // If right child is larger than largest so far 
//         largest = r; 
  
//     if (largest != i) // If largest is not root 
//     { 
//         swap(arr[i], arr[largest]);   
//         heapify(arr, n, largest); // Recursively heapify the affected sub-tree 
//     } 
// } 
  
// // main function to do heap sort 
// void heapSort(int arr[], int n) 
// {    
//     for (int i = n / 2 - 1; i >= 0; i--) // Build heap (rearrange array) 
//         heapify(arr, n, i); 
      
//     for (int i=n-1; i>0; i--) // One by one extract an element from heap 
//     {        
//         swap(arr[0], arr[i]); // Move current root to end        
//         heapify(arr, i, 0); // call max heapify on the reduced heap 
//     } 
// } 

// // Driver program 
// int main()
// {
// 	int arr[] = {9, 8, 4, 6, 7, 3, 5, 2, 1};
//     int n = sizeof(arr)/sizeof(arr[0]); 
  
//     heapSort(arr, n); 

//     for(int i = 0; i < n; ++i){
//     	cout << arr[i] << " ";
//     }

// 	return 0;
// }