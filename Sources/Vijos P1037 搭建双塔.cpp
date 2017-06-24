/*#背包思路
我想到的思路是背包，先二分出来高度，然后判断能不能搭成2*h的高度，然后再从这2*h的高度的水晶里面判断能不能搭出h来。
因为数据比较小，二分换成一个循环也可以。

#动态规划思路
dp[i][j]表示前i个水晶搭出的两个塔差值为j时较矮的塔的高度，然后对于第i个水晶就4种情况，分别讨论一下就行了，讨论看代码注释
注意数组越界情况和前缀和的比较。*/
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define LL long long
#define Lowbit(x) ((x)&(-x))
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1|1
#define MP(a, b) make_pair(a, b)
const int INF = 0x3f3f3f3f;
const int Mod = 1000000007;
const int maxn = 1e5 + 10;
const double eps = 1e-8;
const double PI = acos(-1.0);
typedef pair<int, int> pii;
int a[110], n;
int vis[2020];
int pre[2020][2];

int check(int h) {
	//printf("%d\n", h);
	memset(vis, 0, sizeof(vis));
	memset(pre, -1, sizeof(pre));
	vis[0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 2 * h; j >= a[i]; j--)
			if (!vis[j] && vis[j - a[i]]) {
				vis[j] = 1, pre[j][0] = j - a[i], pre[j][1] = i;
			}
			
	if (!vis[2 * h]) { return 0; }
	memset(vis, 0, sizeof(vis));
	vis[0] = 1;
	for (int i = 2 * h; i != -1; i = pre[i][0]) {
		int id = pre[i][1];
		for (int j = h; j >= a[id]; j--)
			if (!vis[j] && vis[j - a[id]]) {
				vis[j] = 1;
			}
	}
	return vis[h];
}

int main() {
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int sum = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]), sum += a[i];
	}
	int ans = -1;
	for (int i = sum / 2; i >= 1; i--)
		if (check(i)) {
			ans = i;
			break;
		}
	if (ans == -1) { puts("Impossible"); }
	else { printf("%d\n", ans); }
	return 0;
}



#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define LL long long
#define Lowbit(x) ((x)&(-x))
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1|1
#define MP(a, b) make_pair(a, b)
const int INF = 0x3f3f3f3f;
const int Mod = 1000000007;
const int maxn = 1e5 + 10;
const double eps = 1e-8;
const double PI = acos(-1.0);
typedef pair<int, int> pii;
int sum[110], a[110];
int dp[110][2020];

int main() {
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int n, h;
	sum[0] = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		sum[i] = sum[i - 1] + a[i];
	}
	memset(dp, -INF, sizeof(dp));
	//for (int i = 1; i <= 10; i++)
	// printf("%d\n", dp[i][0]);
	dp[1][0] = 0, dp[1][a[1]] = 0;
	for (int i = 2; i <= n; i++)
		for (int j = 0; j <= sum[i]; j++) {
			h = j;                         //第i块不用
			if (h <= sum[i - 1]) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j]);
			}
			h = j - a[i];                  //第i块放到高的上面差值变大
			if (h >= 0 && h <= sum[i - 1]) {
				dp[i][j] = max(dp[i][j], dp[i - 1][h]);
			}
			h = j + a[i];                  //第i块放到矮的上面但是矮的还是矮的
			if (h <= sum[i - 1]) {
				dp[i][j] = max(dp[i][j], dp[i - 1][h] + a[i]);
			}
			h = a[i] - j;                  //第i块放到矮的上面矮的变成高的了
			if (h >= 0 && h <= sum[i - 1]) {
				dp[i][j] = max(dp[i][j], dp[i - 1][h] + h);
			}
		}
	if (dp[n][0] <= 0) { puts("Impossible"); }
	else { printf("%d\n", dp[n][0]); }
	return 0;
}