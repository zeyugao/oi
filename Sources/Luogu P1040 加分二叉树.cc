#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>

using std::cout;
using std::cin;
using std::endl;

//Summary:
//    dp[i][j]
//    dp[i][j] = max{dp[i][root - 1] * dp[root + 1][j] + score[root]}
long long socre[40] = {0};
long long dp[40][40] = {{0}};
int root[40][40] = {{0}};

void Output(int l, int r, int current_root) {
	cout << current_root << " ";
	if (l == r) {
		return;
	}
	if (current_root - 1 >= l) {
		Output(l, current_root - 1, root[l][current_root - 1]);
	}
	if (current_root + 1 <= r) {
		Output(current_root + 1, r, root[current_root + 1][r]);
	}
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> dp[i][i];
		root[i][i] = i;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i; j++) {
			dp[i][j] = 1;
		}
	}
	for (int len = 1; len <= n; len++) {
		for (int start = 1; start + len <= n; start++) {
			int end = start + len;
			for (int temp_root = start; temp_root <= end; temp_root++) {
				long long temp  = dp[start][temp_root - 1] * dp[temp_root + 1][end] + dp[temp_root][temp_root];
				if (temp > dp[start][end]) {
					dp[start][end] = temp;
					root[start][end] = temp_root;
				}
			}
		}
	}
	cout << dp[1][n] << endl;
	Output(1, n, root[1][n]);
	return 0;
}