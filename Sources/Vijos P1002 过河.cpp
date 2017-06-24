#include "stdafx.h"
using namespace std;
int main() {
	int stone[101] = { 0 }, L, S, T, M, dp[10100], hash[10100] = { 0 };
	memset(dp, 127, sizeof(dp));
	cin >> L >> S >> T >> M;
	stone[0] = 0;
	for (int i = 1; i <= M; i++) {
		cin >> stone[i];
	}
	sort(stone, stone + M + 1);
	stone[M + 1] = L;
	if (S == T) {
		int ans = 0;
		for (int i = 1; i <= M; i++) {
			if (stone[i] % S == 0) { ans++; }
		}
		cout << ans;
		return 0;
	}
	for (int i = 0; i <= M; i++)if (stone[i + 1] - stone[i] > 100) { stone[i + 1] = stone[i] + (stone[i + 1] - stone[i]) % 100; }
	for (int i = 1; i <= M; i++) { hash[stone[i]] = 1; }
	for (int i = S; i <= T; i++) {
		if (hash[i]) { dp[i] = 1; }
		else { dp[i] = 0; }
	}
	//从[0,S]之间路程都是跳不到的，从2*S开始，最近的第一次是从(S,0)s开始跳，跳到的最近的是(2*S,0)
	
	//状态是压缩过的，最远路程要更新了，不是L而是新的stone[M+1]
	for (int i = 2 * S; i <= stone[M + 1] + T; i++) {
		for (int jump = S; jump <= T; jump++) {
			if (i < jump) { break; }
			dp[i] = min(dp[i], dp[i - jump]);
		}
		if (hash[i]) { dp[i]++; }
	}
	/*for (int i = 2 * S; i <= stone[M + 1]; i++)
	{
		for (int j = S; j <= T; j++)
		{
			if (j>i)break;
			dp[i] = min(dp[i - j], dp[i]);
		}
		if (hash[i])dp[i]++;
	}*/
	int ans = 0xfffffff;
	for (int i = stone[M + 1]; i <= stone[M + 1] + T; i++) {
		ans = min(ans, dp[i]);
	}
	cout << ans << endl;
	system("pause");
	return 0;
}
