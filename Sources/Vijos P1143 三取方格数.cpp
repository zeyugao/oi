#ifndef _DEBUG
#pragma GCC optimize(2)
#ifdef Full_Cpp_Compiler
#include <codecvt>
#endif
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>
#include <fstream>
#include <Windows.h>
#include <iterator>
#include <set>
#include <process.h>
#include <ctime>
#include <utility>
#include <cctype>
#include <bitset>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a>b?a:b)
#endif // _DEBUG
#include <stdarg.h>
int MAX(int a, int b, int c, int d, int e, int f, int g, int h) {
	int ans = a; ans = max(ans, h);
	ans = max(ans, b); ans = max(ans, g);
	ans = max(ans, c); ans = max(ans, f);
	ans = max(ans, d); ans = max(ans, e);
	return ans;
}
int main() {
	std::ios_base::sync_with_stdio(false);
	int n;
	std::cin >> n;
	
	int map[42][42] = { 0 },
					  //**走了**tot_step步，并且到了横坐标为x的位置
					  dp[42][21][21][21] = { 0 };
	memset(map, 0, sizeof(map));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			std::cin >> map[i][j];
		}
	int tot_step, x_1, x_2, x_3;
	for (tot_step = 1; tot_step <= 2 * n - 2; tot_step++)
		//走了1步时就到(x,2)或(2,y)了，所以后面的是用tot_step-x_1+2而不是tot_step-x_1+1
		//走0步才是原点
		//由于这是直接从第1步（后）开始算的，第0步没有算到，所以在最后需要加上map[1][1]，卡了爆久
		for (x_1 = 1; x_1 <= min(tot_step + 1, n); x_1++)
			for (x_2 = 1; x_2 <= min(tot_step + 1, n); x_2++)
				for (x_3 = 1; x_3 <= min(tot_step + 1, n); x_3++)
					//if (((x_1 != x_2) || (x_1 != x_3) || (x_2 != x_3)) ||
					//(x_1 == n&&x_2 == n&&x_3 == n) || (x_1 == 1 && x_2 == 1 && x_3 == 1)) {
				{
					dp[tot_step][x_1][x_2][x_3] = MAX(
													  dp[tot_step - 1][x_1 - 1][x_2][x_3],
													  dp[tot_step - 1][x_1 - 1][x_2][x_3 - 1],
													  dp[tot_step - 1][x_1 - 1][x_2 - 1][x_3],
													  dp[tot_step - 1][x_1 - 1][x_2 - 1][x_3 - 1],
													  dp[tot_step - 1][x_1][x_2][x_3],
													  dp[tot_step - 1][x_1][x_2][x_3 - 1],
													  dp[tot_step - 1][x_1][x_2 - 1][x_3],
													  dp[tot_step - 1][x_1][x_2 - 1][x_3 - 1]
												  )
												  + map[x_1][tot_step - x_1 + 2] + map[x_2][tot_step - x_2 + 2] + map[x_3][tot_step - x_3 + 2];
					/*if (x_1 == x_2)dp[tot_step][x_1][x_2][x_3] -= map[x_1][tot_step - x_1 + 2];
					if (x_1 == x_3)dp[tot_step][x_1][x_2][x_3] -= map[x_1][tot_step - x_1 + 2];
					if (x_2 == x_3)dp[tot_step][x_1][x_2][x_3] -= map[x_2][tot_step - x_2 + 2];
					*/
					
					if (x_1 == x_2 && x_1 != x_3) { dp[tot_step][x_1][x_2][x_3] -= map[x_1][tot_step - x_1 + 2]; }
					if (x_1 == x_3 && x_1 != x_2) { dp[tot_step][x_1][x_2][x_3] -= map[x_1][tot_step - x_1 + 2]; }
					if (x_2 == x_3 && x_1 != x_3) { dp[tot_step][x_1][x_2][x_3] -= map[x_2][tot_step - x_2 + 2]; }
					if (x_1 == x_2 && x_1 == x_3) { dp[tot_step][x_1][x_2][x_3] -= (map[x_1][tot_step - x_1 + 2] * 2); }
				}
	std::cout << dp[2 * n - 2][n][n][n] + map[1][1]/* + map[1][1] + map[n][n]*/;
	system("pause");
	return 0;
}