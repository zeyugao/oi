#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
const int N = 105;
int n, res = 0, A[N], lis1[N], lis2[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) { scanf("%d", &A[i]); }
	memset(lis1, 0, sizeof(lis1));
	memset(lis2, 0, sizeof(lis2));
	lis1[1] = lis2[n] = 1;
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j < i; j++)
			if (A[i] > A[j]) { lis1[i] = max(lis1[i], lis1[j]); }
		lis1[i]++;
	}
	for (int i = n - 1; i >= 1; i--) {
		for (int j = n; j > i; j--)
			if (A[i] > A[j]) { lis2[i] = max(lis2[i], lis2[j]); }
		lis2[i]++;
	}
	for (int i = 1; i <= n; i++) {
		res = max(res, lis1[i] + lis2[i] - 1);
	}
	printf("%d\n", n - res);
	return 0;
}