#include <iostream>
#include <cstring>
using namespace std;
#define f(a,i,j) for(a= i;a<=j;a++)
long long dp[501][501];
long long map[501][501];
long long r, c;
long long max(long long a, long long b) {
	if (a > b) { return a; }
	else { return b; }
}
long long dfs(long long x, long long y) {
	if (x < 0 || y < 0) { return 0; }
	if (x > r || y > c) { return 0; }
	if (dp[x][y]) { return dp[x][y]; }
	int tmp = 0;
	if (x + 1 <= r && map[x][y] > map[x + 1][y]) {
		tmp = max(tmp, dfs(x + 1, y));
	}
	if (x - 1 >= 0 && map[x][y] > map[x - 1][y]) {
		tmp = max(tmp, dfs(x - 1, y));
	}
	if (y + 1 <= c && map[x][y] > map[x][y + 1]) {
		tmp = max(tmp, dfs(x, y + 1));
	}
	if (y - 1 >= 0 && map[x][y] > map[x][y - 1]) {
		tmp = max(tmp, dfs(x, y - 1));
	}
	dp[x][y] = tmp + 1;
	return dp[x][y];
}
int main() {
	memset(dp, 0, sizeof(dp));
	//为什么h初始化为0时，会有WA，不应该在(1,1)到(r,c)之间都会有初始化吗，何况我在上面加上了防止搜索越界的k判断式了呀
	memset(map, 127, sizeof(map));
	cin >> r >> c;
	long long x, y;
	f(x, 1, r) {
		f(y, 1, c) {
			cin >> map[x][y];
		}
	}
	long long ans = -1;
	f(x, 1, r) {
		f(y, 1, c) {
			ans = max(ans, dfs(x, y));
		}
	}
	cout << ans;
	return 0;
}
