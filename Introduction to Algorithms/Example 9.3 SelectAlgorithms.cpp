//http://www.cnblogs.com/yyxayz/p/4028290.html
#include <stdlib.h>
#include <stdio.h>
#define swap(a,b) (a)^=(b);(b)^=(a);(a)^=(b)
#define MAX 1000

void sort(int* input, int size){
    printf ( "sort arry size = %d\n", size );
    int i,j;
    for(i = 0; i< size ; i++){
        for(j = 0; j<size-i-1;j++){
            if(input[j]<input[j+1]){
                swap(input[j],input[j+1]);
            } 
        }
    }
}
void output(int * input, int size){
    for(;size>0 && *input;size--,input++){
        printf("%d ", *input);
    }
    printf("\n");

}

int partion(int *input, int size, int key){
    printf ( "--------------Step4---------------\n" );
    printf("key = %d \n", input[key]);
    int *head, *tail;
    head = input;
    tail = head + size - 1;
    swap(*head, input[key]);

    int *k = head;
    while(head<tail){
        while(*tail && *k >= *tail){
            tail--;
        }
        if(tail<=head) break;
        swap(*k,*tail);
        k = tail;
        while(*head && *k < *head)
            head++;
        if(head>=tail) break;
        swap(*k,*head);
        k = head;
    }
    output(input, size);
    printf ( "--------------Step4 done--------------\n" );
    return k-input+1;
}

int kselect(int *input, int size, int k){
    printf ( "start element : %d \n", *input );
    if(size<=5){
        sort(input, size);
        return input[k-1];
    }
    int mid[MAX] = {0};
    int midvalue[MAX] = {0};
    int groups = size/5;
    int i;

    printf ( "-----------------step 1, 2--------------\n" );
    for(i = 0; i<groups;i++){
        sort(input+i*5, (i*5+5 > size) ? (size-1):5);
        printf ( "sorted group %d:\n", i );
        output(input+i*5, 5);
        mid[i] = i*5 + 2;
        midvalue[i] = input[i*5 + 2];
    }

    printf ( "-----------------step 1, 2 done--------------\n" );

    printf ( "---------step3-------------\n" );
    sort(midvalue, groups);
    printf ( "---------step3 done-------\n" );
    int m = -1;
    for(i = 0; i<5;i++){
        if(input[mid[i]] == midvalue[groups/2]){
            m = partion(input, size, mid[i]);
        }
    }
    if(m == k){
        return input[m-1];
    }
    if(k<m){
        return kselect(input,m,k);
    }
    else{
        return kselect(input+m, size - m, k-m);
    }
    return 0xffff;
}

int main(){
    int input[] = {1,3,2,10,5,11, 12, 8 ,6, 7};
　　　　　/*输出第７大的元素．*/
    int r = kselect(input,sizeof(input)/sizeof(int), 7);
    printf("result %d \n", r);
    return 0;
}

//
#include <iostream>
#include <time.h>
using namespace std;

const int num_array = 13;
const int num_med_array = num_array / 5 + 1;
int array[num_array];
int midian_array[num_med_array];

//冒泡排序（晚些时候将修正为插入排序）
/*void insert_sort(int array[], int left, int loop_times, int compare_times)
{
    for (int i = 0; i < loop_times; i++)
    {
        for (int j = 0; j < compare_times - i; j++)
        {
            if (array[left + j] > array[left + j + 1])
                swap(array[left + j], array[left + j + 1]);
        }
    }
}*/

/*
//插入排序算法伪代码
INSERTION-SORT(A)                              cost    times
1  for j ← 2 to length[A]                      c1      n
2       do key ← A[j]                          c2      n - 1
3          Insert A[j] into the sorted sequence A[1 ‥ j - 1].     0...n - 1
4          i ← j - 1                           c4      n - 1
5          while i > 0 and A[i] > key           c5      
6             do A[i + 1] ← A[i]               c6      
7             i ← i - 1                        c7      
8          A[i + 1] ← key                      c8      n - 1
*/
//已修正为插入排序，如下：
void insert_sort(int array[], int left, int loop_times)
{
    for (int j = left; j < left+loop_times; j++)
    {
        int key = array[j];
        int i = j-1;
        while ( i>left && array[i]>key )
        {
            array[i+1] = array[i];
            i--;
        }
        array[i+1] = key;
    }
}

int find_median(int array[], int left, int right)
{
    if (left == right)
        return array[left];
    
    int index;
    for (index = left; index < right - 5; index += 5)
    {
        insert_sort(array, index, 4);
        int num = index - left;
        midian_array[num / 5] = array[index + 2];
    }
    
    // 处理剩余元素
    int remain_num = right - index + 1;
    if (remain_num > 0)
    {
        insert_sort(array, index, remain_num - 1);
        int num = index - left;
        midian_array[num / 5] = array[index + remain_num / 2];
    }
    
    int elem_aux_array = (right - left) / 5 - 1;
    if ((right - left) % 5 != 0)
        elem_aux_array++;
    
    // 如果剩余一个元素返回，否则继续递归
    if (elem_aux_array == 0)
        return midian_array[0];
    else
        return find_median(midian_array, 0, elem_aux_array);
}

// 寻找中位数的所在位置
int find_index(int array[], int left, int right, int median)
{
    for (int i = left; i <= right; i++)
    {
        if (array[i] == median)
            return i;
    }
    return -1;
}

int q_select(int array[], int left, int right, int k)
{
    // 寻找中位数的中位数
    int median = find_median(array, left, right);
    
    // 将中位数的中位数与最右元素交换
    int index = find_index(array, left, right, median);
    swap(array[index], array[right]);
    
    int pivot = array[right];
    
    // 申请两个移动指针并初始化
    int i = left; 
    int j = right - 1;  
    
	//不是很懂
    // 根据枢纽元素的值对数组进行一次划分
    while (true)
    {  
        while(array[i] < pivot)
            i++;
        while(array[j] > pivot)
            j--;
        if (i < j) 
            swap(array[i], array[j]); 
        else   
            break;   
    }
    swap(array[i], array[right]); 
    
    /* 对三种情况进行处理：(m = i - left + 1)
    1、如果m=k，即返回的主元即为我们要找的第k小的元素，那么直接返回主元a[i]即可;
    2、如果m>k，那么接下来要到低区间A[0....m-1]中寻找，丢掉高区间;
    3、如果m<k，那么接下来要到高区间A[m+1...n-1]中寻找，丢掉低区间。
    */
    int m = i - left + 1;    
    if (m == k)
        return array[i];
    else if(m > k)  
        //上条语句相当于if( (i-left+1) >k)，即if( (i-left) > k-1 )，于此就与2.2节里的代码实现一、二相对应起来了。
        return q_select(array, left, i - 1, k);  
    else  
        return q_select(array, i + 1, right, k - m);
}

int main()
{
    //srand(unsigned(time(NULL)));
    //for (int j = 0; j < num_array; j++)
    //array[j] = rand();
    
    int array[num_array]={0,45,78,55,47,4,1,2,7,8,96,36,45};
    // 寻找第k最小数
    int k = 4;
    int i = q_select(array, 0, num_array - 1, k);
    cout << i << endl;
    
    return 0;
}