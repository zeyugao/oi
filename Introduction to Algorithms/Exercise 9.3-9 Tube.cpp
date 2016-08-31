/*选择主输油管道的最优位置(使得各喷管长度总和最小的位置)。

算法思想：
1.当n为奇数时，其实就是求median；
2.当n为偶数时，就是第n/2小和第n/2 + 1小的数为边界的闭区间的任何数。

其实这个证明还是蛮简单的，可以移动x轴来观察情况，位于median处(n为奇数)或median范围内(n为偶数)时，设其距离为min，当移动x轴时，移出这个范围，则可以发现所有点(包括median点)到x轴的距离必然大于min。画一下图，就会一目了然。*/
#include <iostream>
#include <time.h>
usingnamespace std;

//随机化分割
int randomized_partition(int* a, int p, int r);
int randomized_select(int* a, int p, int r, int i);

int main()
{
    constint LEN =10;
    int a[LEN] = {3, 5, 9, 56, 100, 23, 34, 22, 94, 100};
    if(LEN%2)
        cout<<"输油管道位于Y = "<<randomized_select(a, 0, LEN -1, (LEN -1)/2)<<"处"<<endl;
    else
    {
        cout<<"输油管道位于Y = "<<randomized_select(a, 0, LEN -1, (LEN -1)/2)<<"与Y = "<<randomized_select(a, 0, LEN -1, (LEN -1)/2+1)<<"之间"<<endl;
    }
    return0;
}

//下标为[p, r]之间的元素
int randomized_partition(int* a, int p, int r)
{
    srand(time(NULL));
    int q = rand()%(r - p +1) + p;
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
        elseif(i < q)
        {
            r = q -1;
            q = randomized_partition(a, p, r);
        }
        else
        {
            p = q +1;
            q = randomized_partition(a, p, r);
        }
    }
    return a[p];
}