#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;
//Summary:
//	dp[step][x1][x2] = max(
//			dp[step-1][x1][x2],//两个都只往下走一格
//			dp[step-1][x1-1][x2],
//			dp[step-1][x1][x2-1],
//			dp[step-1][x1-1][x2-1])+lover[x1][step-x1+2] + lover[x2][step-x2+2];
int main() {
	int m, n;
	cin >> m >> n;
	int lover[55][55] = { 0 };
	
	//读入的时候要注意，内外层的变量是什么
	//这里1行中一个个为x，读入时要放在内层，作为x方向的
	for (int y = 1; y <= m; y++) {
		for (int x = 1; x <= n; x++) {
			cin >> lover[x][y];
		}
	}
	//
	int dp[110][55][55] = { 0 };
	for (int step = 1; step <= m + n - 2; step++) {
		for (int x1 = 1; x1 <= n; x1++) {
			for (int x2 = 1; x2 <= n; x2++) {
				//Anylsis:
				//x1==n&&x2==n是特判，走到了终点，一定要满足步数是估计的那样
				//x1!=x2是一般情况，走的步数+1一定会大于等于横坐标，+1是因为（eg:我往右走了1步，这时应该x在2了）步数从0开始计数，而横坐标从1开始计数
				if ((x1 == n && x2 == n && step == m + n - 2) || (x1 != x2 && step + 1 >= x1 && step + 1 >= x2)) {
				
					int calc_tmp_1 = max(dp[step - 1][x1][x2], dp[step - 1][x1 - 1][x2 - 1]);
					int calc_tmp_2 = max(dp[step - 1][x1 - 1][x2], dp[step - 1][x1][x2 - 1]);
					
					dp[step][x1][x2] = max(calc_tmp_1, calc_tmp_2) + lover[x1][step - x1 + 2] + lover[x2][step - x2 + 2];
				}
			}
		}
	}
	cout << dp[m + n - 2][n][n];
	//system("pause");
	return 0;
}