题意要求尽量缩短时间来完成一件产品，但是由于需要按照步骤，所以多线程的方式不必考虑。dp[i][j]=min（dp[k][p]）+（sum[i][j] - sum[k][j]），dp[i][j]表示完成前i个步骤，且最后一步是在第j台机器上完成。sum[k][j]表示第j台机器完成第1~k个步骤所需要的时间和，但是k与i的距离不宜超过规定的L。式子也可以这样写：dp[i][j]=min（dp[k][p] -  sum[k][j]）+ sum[i][j] ，那么就单单看这项min（dp[k][p] -  sum[k][j]）就行了，这不就是类似于在序列区间a[i-L]~a[i-1]之间找一个最小值的问题？那就可以用单调队列解决了。复杂度为O(n2*m)，是与L无关的。

//#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <deque>
#include <map>
#include <algorithm>
#include <vector>
#include <iostream>
#define pii pair<int,int>
#define INF 0x3f3f3f3f
#define LL long long
#define ULL unsigned long long
using namespace std;
const double PI  = acos(-1.0);
const int N=100100;
const int M=10;
int m, n, K, L;
int t[N][M], dp[N][M];
int que[N][M], idx[N][M], top[M], rear[M];

void calmin(int i)
{
    for(int j=1; j<=n; j++)
    {
        int tar=INF;
        for(int k=1; k<=n; k++)
        {
            if(j==k)    continue;
            tar=min(tar, dp[i][k]);
        }
        tar-=t[i][j];
        while( top[j]<rear[j] && que[rear[j]-1][j]>=tar )    rear[j]--;
        que[rear[j]][j]=tar;
        idx[rear[j]][j]=i;
        rear[j]++;
    }
}

void init()
{
    memset(dp,0x3f,sizeof(dp));
    memset(top,0,sizeof(top));
    memset(rear,0,sizeof(rear));
    memset(dp[0],0,sizeof(dp[0]));
    memset(que,0,sizeof(que));
    memset(idx,0,sizeof(idx));
    for(int i=1; i<=n; i++) //在单个机器上运行所有任务，求区间和
        for(int j=1; j<=m; j++)
            t[j][i]+=t[j-1][i];
    for(int i=1; i<=n; i++)
        rear[i]++;
}
int cal()
{
    init();
    for(int i=1; i<=m; i++) //枚举步骤
    {
        for(int j=1; j<=n; j++) //用第j台机器来完成i项
        {
            while( top[j]<rear[j] && idx[top[j]][j]<i-L)
                top[j]++;       //过期
            int &d=dp[i][j];
            if( top[j]==rear[j] )
            {
                for(int k=1; k<=n; k++)
                {
                    if(k==j)continue;
                    d=min(d, dp[i-1][k]);
                }
                d+=t[i][j]-t[i-1][j];
            }
            else    d=min(d, que[top[j]][j]+t[i][j]+K );
        }
        calmin(i);
    }

    int ans=INF;
    for(int i=1; i<=n; i++)    ans=min(ans, dp[m][i]);
    return ans-K;   //第一步不需要换机器费用
}


int main()
{
    //freopen("input.txt","r",stdin);
    while(~scanf("%d%d%d%d",&m, &n, &K, &L))
    {
        for(int i=1; i<=n; i++) //机器
            for(int j=1; j<=m; j++) //步骤
                scanf("%d",&t[j][i]);
        cout<<cal()<<endl;
    }
    return 0;
}

【思路】

单调队列优化DP。

设f[i][j]表示考虑到第i个步骤，且i步骤由j完成时的最小时间。有转移式：

f[i][j]=min{f[k][p]-sum[k][j]}+sum[i][j]，i-L<=k<=i-1

括号内的部分可以用n个单调队列维护。a[][]为辅助数组，

　　　a[i][j]=min{f[i][k]}-sum[i][j]+K，1<=k<=m

　　 表示f[i][j]时括号中可以取到的最小值，单调队列j维护区间[i-L,i-1]内a[][j]的最小值。

注意单调队列写法。
1 #include<cstdio>
 2 #include<cstring>
 3 #include<iostream>
 4 using namespace std;
 5 
 6 const int maxn = 200000+10;
 7 const int INF  = 1e9+1e9;
 8 
 9 int L[6],R[6],q[maxn][6];
10 int f[maxn][6] , a[maxn][6] , b[maxn][6];
11 int n,m,K,lim;
12 
13 void push(int i,int j) {
14     while(L[j]<R[j] && a[i][j]<=a[q[R[j]-1][j]][j]) R[j]--;
15     q[R[j]++][j]=i;
16 }
17 int pop(int i,int j) {
18     while(L[j]<R[j] && q[L[j]][j]<i-lim) L[j]++;
19     return a[q[L[j]][j]][j];
20 }
21 int read(int& x) {
22     char c=getchar(); while(!isdigit(c))c=getchar();
23     x=0; while(isdigit(c))x=x*10+c-'0',c=getchar();
24 }
25 int main() {
26     read(n),read(m),read(K),read(lim);
27     for(int i=1;i<=m;i++)
28         for(int j=1;j<=n;j++) {
29             read(b[j][i]);
30             b[j][i]+=b[j-1][i];
31         }
32     for(int j=1;j<=m;j++)  push(0,j);
33     for(int i=1;i<=n;i++)
34     {
35         for(int j=1;j<=m;j++)
36             f[i][j]=pop(i,j)+b[i][j];
37         for(int j=1;j<=m;j++) {            //向单调队列中添加a[i][] 
38             a[i][j]=INF;
39             for(int k=1;k<=m;k++) if(k!=j)
40                 a[i][j]=min(a[i][j],f[i][k]);
41             a[i][j]=a[i][j]-b[i][j]+K;
42             push(i,j);
43         }
44     }
45     int ans=f[1];
46     for(int i=1;i<=m;i++) ans=min(ans,f[i]);
47     printf("%d\n",ans);
48     return 0;
49 }