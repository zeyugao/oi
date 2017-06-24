//完全背包
//http://www.voidcn.com/blog/DaD3zZ/article/p-4850772.html
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define DAN 999999999//被假定为最大值 
int f[10010][10010] = {0};
int up[10010] = {0}, down[10010] = {0}; //每个位置点击1次上升的高度和不点击下降的高度
int maxhigh[10010] = {0}, minhigh[10010] = {0}; //上界 和 下界（有管子的就是上、下管子，无管子就是m+1,0）
int n, m, k;
int step = 0; //可以通过的管子数目
int minstep = DAN; //最少点击数

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &up[i], &down[i]);
	}
	for (int i = 0; i <= n; i++) {
		maxhigh[i] = m + 1;
		minhigh[i] = 0;
	}//初始化上、下界
	int x;
	for (int i = 1; i <= k; i++) {
		scanf("%d", &x);
		scanf("%d%d", &minhigh[x], &maxhigh[x]);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			f[i][j] = DAN;
			if (j - up[i - 1] > 0) {
				f[i][j] = min(f[i][j], min(f[i - 1][j - up[i - 1]], f[i][j - up[i - 1]]) + 1);
			}
		}//完全背包部分
		for (int j = m - up[i - 1]; j <= m; j++) {
			f[i][m] = min(f[i][m], min(f[i][j], f[i - 1][j]) + 1);    //到顶的问题
		}
		for (int j = minhigh[i] + 1; j <= maxhigh[i] - 1; j++)
			if (j + down[i - 1] <= m) {
				f[i][j] = min(f[i][j], f[i - 1][j + down[i - 1]]);
			}
		for (int j = 1; j <= minhigh[i]; j++) {
			f[i][j] = DAN;    //在最后一层（即落地，或下管子）都不可以
		}
		for (int j = maxhigh[i]; j <= m; j++) {
			f[i][j] = DAN;    //上管子到顶部不可以
		}
		bool pd = false;
		for (int j = 1; j <= m; j++)
			if (f[i][j] < DAN) {
				pd = true;    //判断在这个位置是否能够过关
			}
		if (!pd) {
			printf("0\n");
			printf("%d", step);
			return 0;
		}//如果不能过关就输出过了几根管子
		else if (maxhigh[i] != m + 1) {
			step++;    //如果经过的是管子，经过管子数+1
		}
	}
	for (int i = 1; i <= m; i++) {
		minstep = min(minstep, f[n][i]);    //从到达终点的各种方案中选择点击数最少的
	}
	printf("1\n");
	printf("%d", minstep);
	return 0;
}