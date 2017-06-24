#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using std::cin;
using std::endl;
using std::cout;



const int kINF = 0xfffff;
int n;
int dp[250][250] = {0};
int sum[250] = {0};
int dp_func(int b_max) {

	//数组的边界要注意
	for (int len = 2; len <= n; len++) {
		for (int begin = 1; begin <= 2 * n - len; begin++) {
			int end = begin + len - 1;
			dp[begin][end] = b_max ? -kINF : kINF;
			
			for (int k = begin; k < end; k++) {
				if (b_max) {
					dp[begin][end] = (std::max)(
										 dp[begin][end],
										 dp[begin][k] + dp[k + 1][end] + sum[end] - sum[begin - 1]);
				}
				else {
					dp[begin][end] = (std::min)(
										 dp[begin][end],
										 dp[begin][k] + dp[k + 1][end] + sum[end] - sum[begin - 1]);
				}
			}
		}
	}
	int ans = b_max ? -kINF : kINF;
	
	for (int i = 1; i <= n; i++) {
		ans = b_max ? (std::max)(ans, dp[i][i + n - 1]) : (std::min)(ans, dp[i][i + n - 1]);
	}
	return ans;
}

int main() {
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		int read;
		cin >> read;
		sum[i + n] = sum[i] = sum[i - 1] + read;
		//cout<<sum[i]<<endl;
	}
	for (int i = 1; i <= n; i++) {
		sum[i + n] += sum[n];
	}
	
	cout << dp_func(false) << endl << dp_func(true);
	
	
	return 0;
}
