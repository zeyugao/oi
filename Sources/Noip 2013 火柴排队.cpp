#include
#include
#define SIZE 100010
using namespace std;
struct NODE {
	int val, pos;
} A[SIZE], B[SIZE];
bool cmp(NODE a, NODE b) {
	return a.val << / span > b.val;
}
int n, i, j, C[SIZE], D[SIZE];
void init() {
	for (i = 0; i << / span > SIZE; i++) { D[i] = 0; }
}
int lowbit(int x) {
	return x & (-x);
}
void update(int x) {
	while (x <= n) {
		D[x]++;
		x += lowbit(x);
	}
}
int getSum(int x) {
	int ans = 0;
	while (x > 0) {
		ans += D[x];
		x -= lowbit(x);
	}
	return ans;
}

int main() {
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%d", &A[i].val);
		A[i].pos = i;
	}
	for (i = 1; i <= n; i++) {
		scanf("%d", &B[i].val);
		B[i].pos = i;
	}
	sort(A + 1, A + n + 1, cmp);
	sort(B + 1, B + n + 1, cmp);
	
	///获得C数组
	for (i = 1; i <= n; i++) {
		C[B[i].pos] = A[i].pos;
	}
	///求逆序数
	int ans = 0;
	for (i = 1; i <= n; i++) {
		update(C[i]);
		ans += (i - getSum(C[i]));
		ans %= 99999997;
	}
	printf("%d\n", ans);
	return 0;
}