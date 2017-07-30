#include <iostream>
#include <algorithm>
#include <string.h>
#include <cstdio>

using std::cout;
using std::cin;
using std::endl;

int map[15] = { 0 };	//储存每一行不适合种草的土地
int way[1 << 13];		//无论土地是否贫瘠，只要满足左右不相邻的条件的一行的可能
int dp[15][(1 << 13) + 2];	//计算到第i行，当前行的方案为j的所有可能情况
int M, N;
int ways;
int mod = 100000000;
int ans = 0;

//Summary:
//	每一行的数据范围不大=>考虑使用状态压缩
//	每一行的状态只与前一行的状态有关
//	预处理是一个妙点
int main() {
	cin >> M >> N;
	int t;
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> t;
			if (t == 0) {
				map[i] |= 1 << (j - 1);
			}
		}
	}
	ways = 0;
	for (int i = 0; i < (1 << N); i++) {
		//向左移一位，将原本在右边的提前到该位上，二者进行比较
		//只有全部位都不一样，才能说明原先在其右边的没有被选到
		if ((i&(i << 1)) == 0) {
			way[ways++] = i;
		}
	}
	for (int i = 1; i <= ways; i++) {
		//现在初始化第一行的dp数组
		//唯有当前行种了草的土地与土地贫瘠的土地一点交集也没有
		//这个方案才可行
		if ((way[i] & map[1]) == 0) {
			dp[1][way[i]] = 1;
		}
	}
	for (int i = 2; i <= M; i++) {
		for (int j = 1; j <= ways; j++) {		//当前行的状态
			for (int k = 1; k <= ways; k++) {	//前一行的状态
				if (((way[j] & map[i]) == 0) && ((way[k] & way[j]) == 0)) {
					//计算的当前行不能与贫瘠的土地有交集
					//不能与上一行有交集
					dp[i][way[j]] = (dp[i][way[j]] + dp[i - 1][way[k]]) % mod;
				}
			}
		}
	}
	for (int i = 1; i <= ways; i++) {
		ans = (ans + dp[M][way[i]]) % mod;
	}
	cout << ans;
	return 0;
}