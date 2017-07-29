#include <iostream>
#include <algorithm>
#include <string.h>
#include <cstdio>

using std::cout;
using std::cin;
using std::endl;

//Summary:
//	dp[i][j][t]
//	第一列选到第i个，第二列选到第j个，总共分了t个
int n, m, k, map[101][3] = { 0 };
int col[101][3] = { 0 };
int dp[101][101][11] = { 0 };
int two[101] = { 0 };
int main() {
	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			col[i][j] = col[i - 1][j] + map[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		two[i] = two[i - 1] + map[i][1] + map[i][2];
	}
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int t = 1; t <= k; t++) {
				dp[i][j][t] = (std::max)(dp[i - 1][j][t], dp[i][j - 1][t]);

				//最后一个的矩形只包含了第一列
				for (int f = 1; f <= i; f++) {
					dp[i][j][t] = (std::max)(dp[i][j][t], dp[f - 1][j][t - 1] + col[i][1] - col[f - 1][1]);
				}
				//最后一个的矩形只包含了第二列
				for (int f = 1; f <= j; f++) {
					dp[i][j][t] = (std::max)(dp[i][j][t], dp[i][f - 1][t - 1] + col[j][2] - col[f - 1][2]);
				}
				//最后一个的矩形包含了两列
				for (int f = 1; f <= (std::min)(i, j); f++) {
					dp[i][j][t] = (std::max)(dp[i][j][t], dp[f - 1][f - 1][t - 1] + two[(std::min)(i, j)] - two[f - 1]);
				}
			}
		}
	}
	cout << dp[n][n][k] << endl;
	return 0;
}