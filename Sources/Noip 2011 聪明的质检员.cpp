#include <iostream>
#include <cmath>

//不要用 unsigned long long 在abs时会溢出
#define LL long long

using namespace std;
LL S;
LL w[200010], v[200010], n, m, L[200010], R[200010];
LL sum[200010] = {0}, cnt[200010] = {0};
LL check(LL x) {
	sum[0] = 0;
	cnt[0] = 0;
	for (int i = 1; i <= n; i++) {
		sum[i] = sum[i - 1];
		cnt[i] = cnt[i - 1];
		if (w[i] >= x) {
			sum[i] += v[i];
			cnt[i]++;
		}
	}
	LL ret = 0;
	for (int i = 1; i <= m; i++) {
		// 前缀和如果要求某一期间的，要减去左区间的1
		ret += (cnt[R[i]] - cnt[L[i] - 1]) * (sum[R[i]] - sum[L[i] - 1]);
	}
	return ret;
}
LL my_abs(LL x) {
	return x < 0 ? -x : x;
}
int main() {
	ios::sync_with_stdio(0);
	cin >> n >> m >> S;
	LL max = 0;
	for (int i = 1; i <= n; i++) {
		cin >> w[i] >> v[i];
		if (w[i] > max) { max = w[i]; }
	}
	for (int i = 1; i <= m; i++) {
		cin >> L[i] >> R[i];
	}
	int l = 0, r = max + 1, mid;
	
	
	LL t;
	LL ans = 1LL << 60;
	while (l <= r) {
		mid = (l + r) >> 1;
		t = check(mid);
		ans = min(ans, my_abs(t - S));
		if (t < S) { // 检验值之和不足，缩小W以让更多的矿石进入，以提高检验值
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}
	print("lld", ans);
	
	return 0;
}
