#include<iostream>
#include<cstdio>
int left[101], right[101], f[101], h[101], len, n, l, r, mid, t, ans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &h[i]);
	}
	f[1] = h[1]; left[1] = 1; len = 1;
	for (int i = 2; i <= n; ++i) {
		for (t = 0, l = 1, r = len, mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1)
			if (f[mid] < h[i]) { l = mid + 1, t = mid; }
			else { r = mid - 1; } if (++t > len) { f[++len] = h[i]; }
		else if (f[t] > h[i]) { f[t] = h[i]; }
		left[i] = len;
	}
	f[1] = h[n]; right[n] = 1; len = 1;
	for (int i = n - 1; i; --i) {
		for (t = 0, l = 1, r = len, mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1)
			if (f[mid] < h[i]) { l = mid + 1, t = mid; }
			else { r = mid - 1; } if (++t > len) { f[++len] = h[i]; }
		else if (f[t] > h[i]) { f[t] = h[i]; }
		right[i] = len;
	}
	for (int i = 2; i <= n; ++i) {
		ans = std::max(ans, left[i - 1] + right[i]);
	}
	printf("%d\n", n - ans);
	return 0;
}