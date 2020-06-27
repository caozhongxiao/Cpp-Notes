#include <iostream>
using namespace std;

//基数排序
int maxbit(int data[], int n) {//辅助函数，求数据的最大位数
    int max = data[0];//先求出最大数，再求其位数
    for (int i = 1; i < n; ++i)
        if (max < data[i])
            max = data[i];
    
    int d = 1;
    int p = 10;
    while (max >= p){
        //p *= 10; // Maybe overflow
        max /= 10;
        ++d;
    }
    return d;
}

void radixSort(int data[], int n) {
    int d = maxbit(data, n);
    int *tmp = new int[n];
    int *count = new int[10]; //计数器
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++) {//进行d次排序

        for(j = 0; j < 10; j++)
            count[j] = 0; //每次分配前清空计数器

        for(j = 0; j < n; j++){
            k = (data[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }

        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶

        for(j = n - 1; j >= 0; j--) {//将所有桶中记录依次收集到tmp中
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }

        for(j = 0; j < n; j++) //将临时数组的内容复制到data中
            data[j] = tmp[j];
        radix = radix * 10;
    }
    delete[] tmp;
    delete[] count;
}