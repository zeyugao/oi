#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#define MOD 1000000007

using namespace std;

int main() {
	int n, m, K;
	scanf_s("%d%d%d", &n, &m, &K);
	char a[2010] = {0}, b[210] = {0};
	scanf_s("%s%s", a + 1, b + 1);
	
	int f[2][210][210], g[2][210][210];
	f[0][0][0] = 1;
	int i;
	for (i = 1; i <= n; i++) {
		f[i % 2][0][0] = 1;
		for (int j = 1; j <= m; j++) {
			for (int k = 1; k <= K; k++) {
				if (a[i] == b[j]) {
					g[i % 2][j][k] = (f[(i - 1) % 2][j - 1][k - 1] + g[(i - 1) % 2][j - 1][k]) % MOD;
				}
				else {
					g[i % 2][j][k] = 0;
				}
				f[i % 2][j][k] = (g[i % 2][j][k] + f[(i - 1) % 2][j][k]) % MOD;
			}
		}
	}
	cout << f[(i - 1) % 2][m][K];
	
	
	return 0;
}
