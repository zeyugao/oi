这是一个数论问题。首先说给定一个M，判断M是否可行。假设两个野人为i和j，设两个人在第x年相遇，则C[i] + x P[i] === C[j] + x P[j] ( Mod M )，x的最小非负解应至少大于L[i]和L[j]的任意一个（相遇时已至少有一个人死亡），或者无解（两人不可能相遇）。对于每对(i,j)都进行检查， 如果所有人都不能相遇，则说明M是一个可行解。对于M应从小到大枚举，这样首次满足条件的M就是解了。

上述式子转化为标准线性同余方程就是 (P[i]-P[j]) * x === C[j] - C[j] ( Mod M )，应保证P[i]-P[j]不为负数。要注意M最小值应不小于任意一个C[i]。

/* 
 * Problem: NOI2002 savage
 * Author: Guo Jiabao
 * Time: 2009.5.20 22:36
 * State: Solved
 * Memo: 线性同余方程
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
const int MAXN=16;
using namespace std;
int C[MAXN],P[MAXN],L[MAXN],N,M,S;

void init()
{
    freopen("savage.in","r",stdin);
    freopen("savage.out","w",stdout);
    scanf("%d",&N);
    S=N;
    for (int i=1;i<=N;i++)
    {
        scanf("%d%d%d",&C[i],&P[i],&L[i]);
        if (C[i] > S)
            S=C[i];
    }
}
int extend_gcd(int a,int b,int &x,int &y)
{
    if (!b)
    {
        x=1;y=0;
        return a;
    }
    else
    {
        int t,d;
        d=extend_gcd(b,a%b,x,y);
        t=x; x=y; y=t-(a/b)*y;
        return d;
    }
}
int mod_eq(int a,int b,int n)
{
    int d,x,y;
    d = extend_gcd(a,n,x,y);
    if (b%d) return -1;
    x = x * b / d % (n / d);
    x = ( x + n / d ) % ( n / d );
    return x;
}
bool legal()
{
    int i,j,x,a,b;
    for (i=1;i<N;i++)
    {
        for (j=i+1;j<=N;j++)
        {
            a=P[j]-P[i];b=C[i]-C[j];
            if (a<0 && b<0)
                a=-a,b=-b;
            if (a<0 && b>0)
                x=a,a=b,b=x;
            x=mod_eq(a,b,M);
            if (!(x==-1 || x>L[i] || x>L[j]))
                return false;
        }
    }
    return true;
}
void solve()
{
    for (M=S;!legal();M++);
    printf("%dn",M);
}
int main()
{
    init();
    solve();
    return 0;
}