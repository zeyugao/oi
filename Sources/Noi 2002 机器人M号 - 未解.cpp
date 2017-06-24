/*该问题的数学模型是数论问题。机器人M号的所有老师就是小于M大于1M的所有约数，M号机器人的独立数就是小于M于M互质的数的个数，即为M的欧拉函数φ(M)。

把M分解为P1^e1P2^e2...*Pk^ek，欧拉函数有公式为

φ(M)=(P1-1)P1^(e1-1) (P2-1)P2^(e2-1) ... (Pk-1)Pk^(ek-1)

于是所有“政客”的独立数之和就是M的奇质因数中选出偶数个不同的质因数乘积的欧拉函数值之和，“军人”则是选出奇数个。“学者”无法直接 算出，然我们知道除了“政客”和“军人”就是学者，只需用小于M的M的所有约数的独立数之和减去“政客”和“军人”的独立数即可。可以证明，M的所有约数 的欧拉函数之和等于M。

求“政客”和“军人”分别的独立数之和，可以递推求出。定义F[i]为M的所有大于2的质因数中的选择i个质因数的欧拉函数和。F[j] = F[j] + F[j-1] * (P[i]-1) 。“政客”的独立数之和就是∑F[i] (i为偶数)，“军人”的独立数之和就是∑F[i] (i为奇数)。*/
/*
 * Problem: NOI2002 robot
 * Author: Guo Jiabao
 * Time: 2009.5.19 17:43
 * State: Solved
 * Memo: 欧拉函数
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
const int MAXK = 1001, MOD = 10000;
using namespace std;
int P[MAXK], E[MAXK], F[MAXK], r1, r2, r3, M = 1, K;
void init() {
	freopen("robot.in", "r", stdin);
	freopen("robot.out", "w", stdout);
	scanf("%d", &K);
	for (int i = 1; i <= K; i++) {
		scanf("%d%d", &P[i], &E[i]);
	}
}
int QuickPower(int a, int k) {
	if (k == 1) {
		return a % MOD;
	}
	int t = QuickPower(a, k / 2);
	t = t * t % MOD;
	if (k % 2) {
		t = t * a % MOD;
	}
	return t;
}
void solve() {
	int i, j, a = 1;
	if (P[1] == 2) {
		a = 2;
	}
	F[0] = 1;
	for (i = a; i <= K; i++)
		for (j = i - a + 1; j >= 1; j--) {
			F[j] = (F[j] + F[j - 1] * (P[i] - 1)) % MOD;
		}
	for (i = 1; i <= K - a + 1; i++)
		if (i % 2) {
			r2 = (r2 + F[i]) % MOD;
		}
		else {
			r1 = (r1 + F[i]) % MOD;
		}
	for (i = 1; i <= K; i++) {
		M = (M * QuickPower(P[i], E[i])) % MOD;
	}
	r3 = (M + MOD + MOD + MOD - r1 - r2 - 1) % MOD;
}
int main() {
	init();
	solve();
	printf("%dn%dn%dn", r1, r2, r3);
	return 0;
}
