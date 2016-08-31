#include <iostream>
#include <time.h>
using namespace std;
//随机化分割
int randomized_partition(int* a, int p, int r);
int randomized_select(int* a, int p, int r, int i);
int main()
{
    int arr[10] = {4, 34, 21, 8, 3, 10, 453, 32, 1, 400};
    int n;
    while(true)
    {
        cout<<"输入第n小的数："<<endl;
        cin>>n;
        cout<<randomized_select(arr, 0, 9, n - 1)<<endl;
    }
    return 0;
}
//下标为[p, r]之间的元素
int randomized_partition(int* a, int p, int r)
{
    srand(time(NULL));
    int q = rand()%(r - p + 1) + p;
    int temp = a[q];
    a[q] = a[r];
    a[r] = temp;
    int j = p;
    for(int i = p; i < r; i++)
    {
        if(a[i] < a[r])
        {
            if(i != j)
            {
                int temp2 = a[i];
                a[i] = a[j];
                a[j] = temp2;
            }
            j++;
        }
    }
     
    temp = a[j];
    a[j] = a[r];
    a[r] = temp;
    return j;
}
//迭代版本
int randomized_select(int* a, int p, int r, int i)
{
    int q = randomized_partition(a, p, r);
    while(p != r)
    {
        if(i == q)
            return a[q];
        else if(i < q)
        {
            r = q - 1;
            q = randomized_partition(a, p, r);
        }
        else
        {
            p = q + 1;
            q = randomized_partition(a, p, r);
        }
    }
    return a[p];
}