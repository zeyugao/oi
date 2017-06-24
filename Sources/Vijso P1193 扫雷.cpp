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
int main() {
	std::ios_base::sync_with_stdio(false);
	long n, mine[10010] = { 0 }, dp[10010][2][2][2] = { 0 };
	std::cin >> n;
	
	for (int i = 1; i <= n; i++) {
		std::cin >> mine[i];
	}
	
	//t-1,t,t+1
	for (int i = 0; i <= 1; i++)
		for (int j = 0; j <= 1; j++)
			for (int k = 0; k <= 1; k++)
				if ((i + j + k) == mine[1]) {
					dp[1][i][j][k]++;
				}
				
	for (long t = 2; t <= n; t++)
		for (int i/*t-1*/ = 0; i <= 1; i++)
			for (int j/*t*/ = 0; j <= 1; j++)
				for (int k/*t+1*/ = 0; k <= 1; k++)
					for (int h/*t-2*/ = 0; h <= 1; h++)
						if (i + j + k == mine[t] && h + i + j == mine[t - 1]) {
							dp[t][i][j][k] += dp[t - 1][h][i][j];
						}
						
	/*
	f(t, 2, n)
		f(i, 0, 1)
		f(j, 0, 1)
		f(k, 0, 1)
		f(h, 0, 1) {
		if ((i + j + k) == mine[t] && (j + i + h) == mine[t - 1]) {
			dp[t][i][j][k] += dp[t - 1][h][i][j];
		}
	}
	*/
	long res = 0;
	
	for (int i = 0; i <= 1; i++)
		for (int j = 0; j <= 1; j++)
			for (int k = 0; k <=/*在这里的错误弄了好久。。。，最后一行后面不能再放地雷了*/ 0; k++) {
				res += dp[n][i][j][k];
			}
			
	std::cout << res << std::endl;
	return 0;
}
