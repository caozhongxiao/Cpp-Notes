#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
//TODO: not passing
//计数排序
void countingSort(vector<int> &arr){
	int len = arr.size();
	int max = arr[0];
	int min = arr[0];
	//找最大最小值
	for(auto i : arr){
		if(i > max) max = i;
		if(i < min) min = i;
	}
	//统计个数
	int *tmp = new int[max-min+1];
	for(int i = 0; i < max-min+1; ++i) 
		tmp[i] = 0;
	for(int i = 0; i < len; ++i){
		tmp[arr[i]-min]++;
	}
	//统计数组，后面的元素等于前面的元素之和
	int sum = 0;
	for(int i = 0; i <= max-min+1; ++i){ //让统计数组存储的元素值，等于相应整数的最终排序位置
		sum += tmp[i]; //tmp[i] += tmp[i-1];
		tmp[i] = sum;
	}
	//输出结果
	do{
		while(tmp[max--])
			arr[--len] = max;
	} while(max--);

	int *res = new int[max-min+1];
	for(int i = len-1; i >= 0; --i){
		res[tmp[arr[i]-min]-1] = arr[i];
		tmp[arr[i]-min]--;
	}
	for(int i = 0; i < max-min+1; ++i){
		arr[i] = res[i];
	}
	delete[] tmp;
	delete[] res;
}

int main()
{
	vector<int> v = {3, 4, 6, 7, 9, 8, 4, 6, 7, 3, 5, 2, 1};
	countingSort(v);
	for(auto it = v.begin(); it != v.end(); ++it){
		cout << *it << " ";
	}

	return 0;
}