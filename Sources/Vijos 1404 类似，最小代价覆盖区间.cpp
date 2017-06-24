#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;
#define lp (p << 1)
#define rp (p << 1|1)
#define getmid (l,r) (l + (r - l) / 2)
#define MP (a,b) make_pair(a,b)
typedef long long ll;
const ll INF = 1e16;
const int maxn = 90000;

int N, M, E;
ll dp[maxn];

struct node {
	int st, ed, sl;
} t[100010];

struct SegTree {
	ll t[maxn << 2];
	
	//建树
	void Build(int p, int l, int r) {
		t[ p] = INF;
		if (l == r) {
			return;
		}
		int mid = getmid(l, r);
		Build(lp, l , mid);
		Build(rp, mid + 1, r);
	}
	
	//更新位置为a，root=p，临时区间为[l,r]的值为c
	void Update(int a, ll c, int p, int l, int r) {
		if (l == r) {
			t[ p] = min(t[p], c);
			return;
		}
		int mid = getmid(l, r);
		if (a <= mid) { Update(a, c, lp, l, mid); }
		else { Update(a , c, rp, mid + 1, r); }
		t[ p] = min(t[lp], t[ rp]);
	}
	
	
	//查询区间[a,b]中，root为p，临时区间为[l,r]的最小值
	ll Query(int a, int b, int p, int l, int r) {
		if (a <= l && r <= b) {
			return t[p ];
		}
		int mid = getmid(l, r);
		ll res = INF;
		if (a <= mid) { res = min(res, Query(a, b, lp, l, mid)); }
		if (b > mid) { res = min(res, Query(a, b, rp, mid + 1, r)); }
		return res;
	}
} ST;

bool cmp(node a, node b) {
	return a .ed < b.ed;
}

//dp[t[i].ed] = min{dp[k] + t[i].sl} k∈[t[i].st-1,t[i].ed-1] //往前查询能与前面的对接上，保证全部覆盖
int main() {
	scanf("%d%d%d", &N, &M, &E);
	for (int i = 0; i < maxn; ++i) {
		dp[i] = INF;
	}
	ST.Build(1, 1, maxn);
	++M;
	++E;
	for (int i = 1; i <= N; ++i) {
		scanf("%d%d%d", &t[i].st, &t[i].ed, &t[i].sl);
		++t[i].st;
		++t[i].ed;
	}
	sort(t + 1, t + N + 1, cmp);
	for (int i = 1; i <= N; ++i) {
		if (t[i].st > E || t[i].ed < M) {
			continue;
		}
		if (t[i].st <= M) {
			dp[t[i].ed] = min(dp[t[i].ed], (ll)t[i].sl);
		}
		else {
			//bot为t[i].st，若st<M，更新为M；top为ed，更新方法同上
			int bot = max(t[i].st - 1, M), top = min(E, max(t[i].ed - 1, M));
			
			//查询[bot，top]区间中，dp最小值
			ll tmin = ST.Query(bot, top, 1, 1, maxn);
			dp[t[i].ed] = min(dp[t[i].ed], tmin + t[i].sl);
		}
		//更新dp
		ST.Update(t[i].ed, dp[t[i].ed], 1, 1, maxn);
	}
	if (dp[E] >= INF) { printf("-1\n"); }
	else { printf("%I64d\n" , dp[E]); }
	return 0;
}