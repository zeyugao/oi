#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#define min(a,b) ((a)<(b)?(a):(b))
int main() {
	int n, c, power[51], local[51], P = 0, sum[51][51], prep[51], dp[51][51][2], dist[51][51];
	
	memset(power, 0, sizeof(power));
	memset(sum, 0, sizeof(sum));
	memset(prep, 0, sizeof(prep));
	memset(dist, 0, sizeof(dist));
	memset(local, 0, sizeof(local));
	std::cin >> n >> c;
	prep[0] = 0;
	for (int i = 1; i <= n; i++) {
		std::cin >> local[i] >> power[i];
		P += power[i];
		prep[i] = prep[i - 1] + power[i];
	}
	for (int i = 0; i <= 50; i++)
		for (int j = 0; j <= 50; j++) { dp[i][j][0] = dp[i][j][1] = 0xfffffff; }
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++) {
			sum[i][j] = prep[j] - prep[i - 1];
			dist[i][j] = local[j] - local[i];
		}
	dp[c][c][0] = dp[c][c][1] = 0;
	for (int l = c; l >= 1; l--) {
		for (int r = c; r <= n; r++) {
			if (l < c) {
				dp[l][r][0] = min(dp[l + 1][r][0] + (P - sum[l + 1][r]) * dist[l][l + 1], dp[l + 1][r][1] + (P - sum[l + 1][r]) * dist[l][r]);
			}
			if (r > c) {
				dp[l][r][1] = min(dp[l][r - 1][1] + (P - sum[l][r - 1]) * dist[r - 1][r], dp[l][r - 1][0] + (P - sum[l][r - 1]) * dist[l][r]);
			}
		}
	}
	std::cout << min(dp[1][n][0], dp[1][n][1]);
	return 0;
}