/*这道题很显然是dp啊，dp[k][i][j]表示第k次滑到（i,j）的最大价值。
这里有些麻烦，因为有四个方向，我选取一个方向来分析，比如从左向右滑动，那么dp[i][j][k]=max{dp[i][j][t]+k-t} 这里可以把k从max里拿出来，
那么dp[i][j][k]=max{dp[i][j][t]-t}+k,这样就看出了max的值和k无关，注意一下t的取值范围，t>=1&&k-t不能大于最大的滑动步数&&从（i,k）到（i,t）之间当然不能有障碍。
然后考虑4个方向，就可以用单调队列优化*/

#include<cstdio>
#include<iostream>
#include<cstring>
#define Maxn 210
using namespace std;

char maze[Maxn][Maxn];
int dp[Maxn][Maxn][Maxn];
int step[Maxn], dir[Maxn], q[Maxn];
int main() {
	int n, m, x, y, t, a, b;
	scanf("%d%d%d%d%d", &n, &m, &x, &y, &t);
	for (int i = 1; i <= n; i++) {
		scanf("%s", maze[i] + 1);
	}
	for (int i = 1; i <= t; i++) {
		scanf("%d%d%d", &a, &b, dir + i);
		step[i] = b - a + 1;
	}
	memset(dp, 0x80, sizeof dp);
	dp[0][x][y] = 0;
	for (int k = 1; k <= t; k++) {
		if (dir[k] > 2) {
			for (int i = 1; i <= n; i++) {
				int s = 0, e = -1;
				if (dir[k] == 4) {
					for (int j = 1; j <= m; j++) {
						if (maze[i][j] == 'x') {s = 0, e = -1; continue;}
						while (s <= e && dp[k - 1][i][q[e]] - q[e] <= dp[k - 1][i][j] - j) { e--; }
						q[++e] = j;
						if (q[s] + step[k] < j) { s++; }
						dp[k][i][j] = dp[k - 1][i][q[s]] + j - q[s];
					}
				}
				else {
					for (int j = m; j >= 1; j--) {
						if (maze[i][j] == 'x') {s = 0, e = -1; continue;}
						while (s <= e && dp[k - 1][i][q[e]] + q[e] <= dp[k - 1][i][j] + j) { e--; }
						q[++e] = j;
						if (q[s] - step[k] > j) { s++; }
						dp[k][i][j] = dp[k - 1][i][q[s]] - j + q[s];
					}
				}
			}
		}
		else {
			for (int j = 1; j <= m; j++) {
				int s = 0, e = -1;
				if (dir[k] == 2) {
					for (int i = 1; i <= n; i++) {
						if (maze[i][j] == 'x') {s = 0, e = -1; continue;}
						while (s <= e && dp[k - 1][q[e]][j] - q[e] <= dp[k - 1][i][j] - i) { e--; }
						q[++e] = i;
						if (q[s] + step[k] < i) { s++; }
						dp[k][i][j] = dp[k - 1][q[s]][j] + i - q[s];
					}
				}
				else {
					for (int i = n; i >= 1; i--) {
						if (maze[i][j] == 'x') {s = 0, e = -1; continue;}
						while (s <= e && dp[k - 1][q[e]][j] + q[e] <= dp[k - 1][i][j] + i) { e--; }
						q[++e] = i;
						if (q[s] - step[k] > i) { s++; }
						dp[k][i][j] = dp[k - 1][q[s]][j] - i + q[s];
					}
				}
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			ans = max(ans, dp[t][i][j]);
		}
	printf("%d\n", ans);
	return 0;
}

/*朴素的动规很好考虑，f[i, x, y]表示第i个时间段结束的时候在(x, y)位置的最大滑动距离。那么就有朴素方程：*/
f[i, x, y] = max{ f[i - 1, x + s, y] + s }(d[i] = 1)
			 max{ f[i - 1, x - s, y] + s }(d[i] = 2)
			 max{ f[i - 1, x, y + s] + s }(d[i] = 3)
			 max{ f[i - 1, x, y - s] + s }(d[i] = 4)
			 /*
			 其中s为0到最远滑行距离，也就是min{第i时间段的时间, 障碍物到当前点的距离}
			 时间复杂度O(knm*最大时间)，其中最大时间<=max(n, m)
			 优化：
			 考虑d[i] = 1的情况：*/
			 f[i, x, y] = max{ f[i - 1, x + s, y] + s }(d[i] = 1)
						  = max{ f[i - 1, x + s, y] + (x + s) } - x
							令g(k) = f[i - 1, x + s, y] + (x + s)，那么：
									  f[i, x, y] = max{ g(k) } - x
											  
											  
											  
											  Code:
#include <cstdio>
#include <cstring>
											  
#define MAX(x, y) if (x < y) x = y;
struct Item {
	int time, value;
	Item(const int t = 0, const int v = 0): time(t), value(v) { }
};
char map[201][201];
int n, m, x0, y0, p, last[201], d[201], f[201][201][201];
inline void update(const int i, int x, int y, const int dx, const int dy) {
	static Item Q[201];
	static int head, tail;
	head = 0, tail = -1;
	for (int now = 1; x >= 1 && x <= n && y >= 1 && y <= m; x += dx, y += dy, ++now) {
		if (map[x][y] != '.') {
			head = 0, tail = -1;
			f[i][x][y] = 0xC0C0C0C0;
			continue;
		}
		while (head <= tail && f[i - 1][x][y] - now >= Q[tail].value) { --tail; }
		Q[++tail] = Item(now, f[i - 1][x][y] - now);
		while (head + 1 <= tail && now - Q[head].time > last[i]) { ++head; }
		f[i][x][y] = Q[head].value + now;
	}
}
int main() {
	memset(f[0], 0xC0, sizeof(f[0]));
	scanf("%d%d%d%d%dn", &n, &m, &x0, &y0, &p);
	for (int i = 1; i <= n; ++i) {
		scanf("%sn", &map[i][1]);
	}
	for (int i = 1, st, ed; i <= p; ++i) {
		scanf("%d%d%d", &st, &ed, d + i);
		last[i] = ed - st + 1;
	}
	
	f[0][x0][y0] = 0;
	for (int i = 1; i <= p; ++i)
		switch (d[i]) {
		case 1: for (int y = 1; y <= m; ++y) { update(i, n, y, -1,  0); } break;
		case 2: for (int y = 1; y <= m; ++y) { update(i, 1, y, +1,  0); } break;
		case 3: for (int x = 1; x <= n; ++x) { update(i, x, m,  0, -1); } break;
		case 4: for (int x = 1; x <= n; ++x) { update(i, x, 1,  0, +1); }
		}
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			MAX(ans, f[p][i][j]);
		}
	printf("%d", ans);
}
/*首先考虑对于时间t来dp：
f[t][i][j]表示在第t时刻在第i行第j列所能获得的最长距离。
转移方程显然：
f[t][i][j]=max(f[t-1][i][j],f[t][i*][j*]+1)(i*,j*为上一个合理的位置)
这样时间复杂度为O(TNM)，可以过50%,但对于100%超时。
所以考虑一下另一种dp方式：
f[k][i][j]表示在第k段滑行区间中在第i行第j列获得最长距离。
考虑转移：
对于d==1（即向上走），可以发现每一列的信息是可以转移的，同时，每一列的信息也是可以通过单调队列维护的信息十分快速的求出，可以脑补，复杂度为O(KNM)。*/


