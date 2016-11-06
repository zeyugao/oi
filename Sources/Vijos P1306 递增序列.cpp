/*简单dp，重构解，，确实恶心，，
dp[i,j]表示前i个最后一个是[i-j+1..i]，然后就非常简单了。。*/

/*我的思路类似，dp[n,j]前n个数，最后一个数在j（开始）时的最大长度，dp[n,j]=max{dp[j-1][t] ，j与t符合各种要求即可*/
#include <bits/stdc++.h>
using namespace std;

char str[100];
int dp[100][100];

bool biger(int i, int j, int k, int w)
{
        if (i > j || k > w) return 1;
        while (i < j && str[i] == '0') i++;
        while (k < w && str[k] == '0') k++;
        if (j-i != w-k) return j-i > w-k;
        while (i <= j) {
                if (str[i] != str[k]) return str[i] > str[k];
                i++, k++;
        }
        return 0;
}

bool print(int i, int j)
{
        if (i-j == 0) {
                for (int k = 1; k <= i; k++)
                        putchar(str[k]);
                return true;
        }
        for (int k = 1; k <= i-j; k++)
                if (dp[i-j][k]+1 == dp[i][j] && biger(i-j+1, i, i-j-k+1, i-j)) {
                        if (print(i-j, k)) {
                                putchar(',');
                                for (int p = i-j+1; p<=i; p++)
                                        putchar(str[p]);
                                return true;
                        }
                }
        return false;
}

int main()
{
        cin >> str+1;
        int n = strlen(str+1);
        memset(dp, -127/3, sizeof dp);
        for (int i = 1; i <= n; i++)
                dp[i][i] = 1;
        for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                        if(j <= i)
                                for (int k = 1; k <= i-j; k++)
                                        if (biger(i-j+1, i, i-j-k+1, i-j))
                                                dp[i][j] = max(dp[i][j], dp[i-j][k]+1);
                }
        }
        int ans = 1;
        for(int i = 2; i <= n; i++)
                if (dp[n][i] > dp[n][ans])
                        ans = i;
        print(n, ans);
        return 0;
}

/*
简单一维DP。。还耗了我两节课。。
忘记去年的思路了。。重新写了一个。。思路简单。。直接给方程了：
f[i]=max{f[k]|s[k+1,i]>m} m表示前i个数划分k逗号的最大值。。
唯一委琐的应该就是打印吧。。反正我的打印很委琐。。
程序如下：
var t:string;
s,m:array[0..80,0..80] of int64;
f,g:array[1..80] of int64;
i,j,k,l:longint; max:int64;
procedure print(n:longint);
begin
if n=0 then exit;
print(g[n]);
if n<>l then write(copy(t,k+1,n-k)+',') else writeln(copy(t,k+1,n-k));
k:=n;
end;
begin
readln(t);
l:=length(t);
for i:=1 to l do
for j:=i to l do
val(copy(t,i,j-i+1),s);
fillchar(f,sizeof(f),0);
for i:=1 to l do m:=s[1,i];
for i:=1 to l do
begin
max:=-1;
for k:=0 to i-1 do
begin
if (f[k]>max)and(s[k+1,i]>m[k,f[k]]) then
begin
f[i]:=f[k]+1;
m:=s[k+1,i];
g[i]:=k;
end else
if (f[k]=max)and(s[k+1,i]=m[k,f[k]]) then
begin
m:=s[k+1,i];
g[i]:=k;
end;
end;
end;
k:=0;
print(l);
end.
*/