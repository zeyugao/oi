#include <iostream>

using namespace std;

int main() {
	int N, M;
	cin >> N >> M;
	int c[110];
	bool check[1010] = { 0 };
	for (int i = 1; i <= N; i++) {
		cin >> c[i];
	}
	int dp[10010] = { 0 };
	dp[0] = 1;
	for (int i = 1; i <= N; i++) {
		for (int V = M; V >= c[i]; V--) {
			dp[V] += dp[V - c[i]];
		}
	}
	
	cout << dp[M] << endl;
	
	return 0;
}