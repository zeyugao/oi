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
#define GetValue(a,b,c,d) (map[a*1+b*2+c*3+d*4+1])
int main() {
	int n, m;
	std::cin >> n >> m;
	int card[5] = { 0 }, map[351] = { 0 }, dp[41][41][41][41] = { 0 };
	for (int i = 1; i <= n; i++) { std::cin >> map[i]; }
	for (int i = 1; i <= m; i++) { int tmp; std::cin >> tmp; card[tmp]++; }
	dp[0][0][0][0] = map[1];
	for (int a = 0; a <= card[1]; a++) {
		for (int b = 0; b <= card[2]; b++) {
			for (int c = 0; c <= card[3]; c++) {
				for (int d = 0; d <= card[4]; d++) {
					if (a != 0) { dp[a][b][c][d] = max(dp[a][b][c][d], dp[a - 1][b][c][d] + GetValue(a, b, c, d)); }
					if (b != 0) { dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b - 1][c][d] + GetValue(a, b, c, d)); }
					if (c != 0) { dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b][c - 1][d] + GetValue(a, b, c, d)); }
					if (d != 0) { dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b][c][d - 1] + GetValue(a, b, c, d)); }
					/*
					int temp = 0;
					if (a)temp = max(temp, dp[a - 1][b][c][d]);
					if (b)temp = max(temp, dp[a][b-1][c][d]);
					if (c)temp = max(temp, dp[a][b][c-1][d]);
					if (d)temp = max(temp, dp[a][b][c][d-1]);
					dp[a][b][c][d] = temp += map[a * 1 + b * 2 + c * 3 + d * 4 + 1];*/
				}
			}
		}
	}
	std::cout << dp[card[1]][card[2]][card[3]][card[4]];
#ifdef  _DEBUG
	system("pause");
#endif //  _DEBUG
	return 0;
}
