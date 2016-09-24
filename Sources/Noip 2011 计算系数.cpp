#ifndef _DEBUG
#pragma GCC optimize(2)
#ifdef Full_Cpp_Compiler
#include <codecvt>
#endif
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>
#include <fstream>
#include <Windows.h>
#include <iterator>
#include <set>
#include <process.h>
#include <ctime>
#include <utility>
#include <cctype>
#include <bitset>
#include <stdarg.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a>b?a:b)
#endif // _DEBUG
int mod = 10007;
int slowpower(int a, int b) {
	int t = 1;
	for (int i = 0; i < b; i++) {
		t = t*a%mod;
	}
	return t;
}
int quickpower(int a, int b) {
	int t = 1, y = a;
	while (b != 0) {
		if (b & 1)t = (t*y) % mod;
		y = (y*y) % mod;
		b = b >> 1;
	}
	return t;
}
int main() {
	std::ios_base::sync_with_stdio(false);
	int a, b, k, n, m;
	std::cin >> a >> b >> k >> n >> m;
	int C[1200][1200] = { 0 };
	int ans = 1;
	//一开始总有两个点会答案错误，才发现是这里有问题，上codevs获取数据，手动调试，发现在错误的答案上，ans会直接溢出，难怪错了
	a %= mod, b %= mod;
	ans = quickpower(a,n)*quickpower(b,m)%mod;
	for(int i =0;i<=k;i++)C[i][0] = C[i][i] = 1;
	for (int i = 0; i <= k; i++)
	{
		for (int j = 1; j <= i; j++)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	}
	ans = (C[k][n] * ans) % mod;
	//ans = (C[k][m] * ans) % mod;也行
	std::cout << ans << std::endl;;
	return 0;
}
