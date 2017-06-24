#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
using std::cin;
using std::endl;
using std::cout;

int p[110 * 2 + 2] = {0};
int dp[110 * 2 + 2][110 * 2 + 2] = {0};
//dp
//dp[i][j] = max{dp[i][k] + dp[k+1][j] + p[i]*p[k]*p[j]}
//代表了从i到j中全部进行了合并后的最大值
int main() {
	int n;
	
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> p[i];
		p[i + n] = p[i];
	}
	for (int i = 1; i < n; ++i) { //the number of having combined
		for (int j = 1; j <= 2 * n - i; j++) { //the start pos
			for (int k = j + 1; k <= j + i; k++) { //the combined pos
				dp[j][j + i] = (std::max)(dp[j][i + j],
										  //注意审题，是哪几个能量的的相互乘积
										  dp[j][k - 1] + dp[k][j + i] + p[j] * p[k] * p[j + i + 1]);
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans = (std::max)(ans, dp[i][i + n - 1]);
	}
	cout << ans << endl;
	return 0;
}