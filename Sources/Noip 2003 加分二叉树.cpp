//二叉树的中序遍历是顺序的，如果中序遍历是[1,6,2,7,8,3,4,9]如果根结点是root，那么root左边的就是左孩子，右边的是右孩子

//对于区间[i,j]其最大加分为选取其中一个作为根R，其左边[i,R-1]的最大加分乘以[R+1,j]区间最大加分+Value[R]，
//对于所有可能的R取表达式最大值.状态转移方程：
//f[i][j] = max{f[i][k-1]*f[k+1][j],k∈[i,j]}//k是dp的根节点
//重复dfs，记录值

//初始值for i=1 to n f[i][i]=v[i];
//输出便利的方法是：每次记录取到最大值时的根节点编号，设Node[i][j]=x表示在[i][j]区间取到最大加分的数的根节点为x
#include <stdio.h>
int n;
int v[40];
__int64 arr[40][40];//表示从i到j的最大加分
int nod[40][40];//表示[i,j]区间根
__int64 gm(int b, int e) { //Get Max
	int i; __int64 x;
	if (arr[b][e] > 0) { return arr[b][e]; } //记忆化搜索
	//缺少左或右子树的情况
	if (e - b < 2) {nod[b][e] = b; arr[b][e] = v[b] + v[e]; return arr[b][e];}
	
	for (i = b + 1; i < e; i++) {
		x = gm(b, i - 1) * gm(i + 1, e) + v[i];
		if (x > arr[b][e]) {
			arr[b][e] = x;
			nod[b][e] = i;
		}
	}
	return arr[b][e];
}
void print(int b, int e) { //输出先序遍历
	if (b == e) {printf("%d ", b); return;}
	printf("%d ", nod[b][e]);
	if (nod[b][e] != b) { print(b, nod[b][e] - 1); }
	if (nod[b][e] != e) { print(nod[b][e] + 1, e); }
}
int main() {
	int i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) for (j = 1; j <= n; j++) { arr[i][j] = -1; }
	for (i = 1; i <= n; i++) {
		scanf("%d", &v[i]); arr[i][i] = v[i];
		nod[i][i] = i;
	}
	printf("%I64d\n", gm(1, n));
	//for (i=1;i<=n;i++){ for (j=1;j<=n;j++)printf("%3d",nod[i][j]);printf("\n");}
	print(1, n);
	//getch();
	return 0;
}
/*
中序遍历有序说明在[i,j]区间内的最大加分可由选择的中间点表示状态
*/