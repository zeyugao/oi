#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#define MAXN 5000000 + 10
int phi[MAXN] = { 0 };
int n;
unsigned long long phi_prefix_sum[MAXN] = { 0 };
void GetPhiTable() {

	//没看懂
	//TODO:Understand it
	for (int i = 2; i <= n; i++) {
		if (!phi[i]) {
			for (int j = i; j <= n; j += i) {
				if (!phi[j]) {
					phi[j] = j;
				}
				phi[j] = phi[j] / i * (i - 1);
			}
		}
	}
	
	
	//以上φ函数打表预处理
	
	//以下是前缀和预处理
	for (int i = 1; i <= n; i++) {
		phi_prefix_sum[i] = phi_prefix_sum[i - 1] + (unsigned long long) phi[i] * phi[i];
	}
	
}
int main() {
	std::cin >> n;
	GetPhiTable();
	int t, a, b;
	
	while (t--) {
		std::cin >> a >> b;
		std::cout << "Case " << t << ": " << phi_prefix_sum[b] - phi_prefix_sum[a - 1] << std::endl;
	}
	
	return 0;
}