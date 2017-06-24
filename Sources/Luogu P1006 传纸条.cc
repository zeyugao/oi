#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define MAXNUM 10000
#define LEN 4

//Summary:
//    dp[step][x1][x2] = max(
//            dp[step-1][x1][x2],//两个都只往下走一格
//            dp[step-1][x1-1][x2],
//            dp[step-1][x1][x2-1],
//            dp[step-1][x1-1][x2-1])+lover[x1][step-x1+2] + lover[x2][step-x2+2];
int main() {
	int m, n;
	cin >> m >> n;
	int lover[55][55] = { 0 };
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
				//在开始或者终点的时候没有值
				//开始：x1==x2
				//终点：x1==n&&x2==n
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