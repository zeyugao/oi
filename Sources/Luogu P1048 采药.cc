#include <iostream>

using namespace std;

int main() {
	int T, M;
	cin >> T >> M;
	
	int time[101], value[101];
	
	for (int i = 1; i <= M; i++) {
		cin >> time[i] >> value[i];
	}
	int dp[1001] = {0};
	
	for (int i = 1; i <= M; i++) {
		for (int j = T; j >= time[i]; j--) {
			dp[j] = max(dp[j], dp[j - time[i]] + value[i]);
		}
	}
	cout << dp[T] << endl;
	return 0;
}