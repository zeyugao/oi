//初始化的重要性
//一开始，c[1001],w[1001],f[1001]没有加{0}，全部WA
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
	int c[1001] = {0}, w[1001] = {0}, T, M, f[1001] = {0};
	cin >> T >> M;
	for (int i = 1; i <= M; i++) {
		cin >> c[i] >> w[i];
	}
	for (int i = 1; i <= M; i++) {
		for (int j = T; j >= c[i]; j--) {
			f[j] = max(f[j], f[j - c[i]] + w[i]);
		}
	}
	cout << f[T] << endl;;
	return 0;
}

