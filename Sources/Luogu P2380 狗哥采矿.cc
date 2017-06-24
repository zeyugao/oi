#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>

using namespace std;

int main() {
	std::ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	
	while (n != 0 && m != 0) {
		//0表示yeyenum
		//1表示bloggium
		
		int to_south_sum[510][510] = { 0 }, to_north_sum[510][510] = { 0 };
		//开始读入yeyenum
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				int k;
				cin >> k;
				to_south_sum[i][j] = to_south_sum[i][j - 1] + k;
			}
		}
		
		//开始读入bloggium
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				int k;
				cin >> k;
				to_north_sum[i][j] = to_north_sum[i - 1][j] + k;
			}
		}
		int ans = -0xff;
		
		int dp[510][510] = { 0 };
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				dp[i][j] = (std::max)(dp[i - 1][j] + to_south_sum[i][j],
									  dp[i][j - 1] + to_north_sum[i][j]);
				if (dp[i][j] > ans) {
					ans = dp[i][j];
				}
			}
		}
		cout << ans << endl;
		cin >> n >> m;
	}
	return 0;
}