/*和矩阵链乘法相似..{简直一模一样..}
sum表示从第i个数到第j个数的最优解..枚举从第k,k+1处断开的可能性.k=1,2,……,j-1...状态转移方程为..
sum:=0 i=j
sum:=max(data+data[k+1,j]+sum+sum[k+1,j])..0<i<j<=n
其中data表示从第i个数到第j个数的和..这样可以节约时间..
找一个数组记录路径..path表示从第i个数到第j个数是从哪里断开的..在替换sum时顺便也修改path的值..然后一个递归打印..
第3个问有点棘手..但其实稍为想一想..就很容易解决..由于我们打印方案的时候就已经是从内到外的..所以只要在打印方案的时候..找一个数组..记录和..然后最后再打印数组..就0K了..
感谢xjdx的提醒..本来我想放弃这一条方案不唯一的题的了..但是经提醒后..我把枚举k由从1枚举到j-1改为从j-1枚举到1.因为要左边加括号优先..即右边断开优先..于是改进后..全对..0ms..{辉煌啊.....撒花..鼓掌..~~!!}

DP的方程下面说得很清楚了

记录分割点然后递归,mid[a,b]为a,b区间的分割点

记录括号好写
根据mid[a,b]二分递归,若a=b则终止

中间和,根据输出顺序(楼下epicwu有说明)
要分4种情况

1.b-a=1
直接输出本区间的和

2.a<mid[a,b]<b-1
先搜索区间(a,mid[a,b])
然后搜区间(mid[a,b]+1,b)
然后输出本区间的和

3.mid[a,b]=a
先搜索区间(a+1,b)
然后输出本区间的和

4.mid[a,b]=b
先搜索区间(a,b-1)
然后输出本区间的和
*/
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n, i, j, k, num[21], process[21][21], zhong[23];
int f[21][21], s[21] = {0};
void output(int l, int r) {
	printf("(");
	if (process[l][r] == l) { printf("%d", num[l]); }
	else { output(l, process[l][r]); }
	printf("+");
	if (process[l][r] == r - 1) { printf("%d", num[r]); }
	else { output(process[l][r] + 1, r); }
	printf(")");
}
void out_put(int l, int r) {
	if (process[l][r] != l) {
		out_put(l, process[l][r]);
		printf("%d ", s[process[l][r]] - s[l - 1]);
	}
	if (process[l][r] != r - 1) {
		out_put(process[l][r] + 1, r);
		printf("%d ", s[r] - s[process[l][r]]);
	}
}
int main() {
	scanf("%d", &n);
	memset(f, 0x3f, sizeof(f));
	for (i = 1; i <= n; ++i) {
		scanf("%d", &num[i]);
		s[i] = s[i - 1] + num[i];
		f[i][i] = num[i];
	}
	for (i = 1; i <= n; ++i)
		for (j = i - 1; j >= 1; --j)
			for (k = j; k < i; ++k) {
				int tmp1, tmp2;
				if (k == j) { tmp1 = 0; }
				else { tmp1 = f[j][k]; }
				if (k == i - 1) { tmp2 = 0; }
				else { tmp2 = f[k + 1][i]; }
				if (f[j][i] >= tmp1 + tmp2 + s[i] - s[j - 1]) {
					f[j][i] = tmp1 + tmp2 + s[i] - s[j - 1];
					process[j][i] = k;
				}
			}
	output(1, n);
	printf("\n%d\n", f[1][n]);
	out_put(1, n);
	printf("%d", s[n]);
}