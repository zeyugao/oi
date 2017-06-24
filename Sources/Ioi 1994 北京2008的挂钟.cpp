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
#include <cmath>
#include <Windows.h>
#include <iterator>
#include <set>
#include <process.h>
#include <ctime>
#include <utility>
#include <cctype>
#include <bitset>
#endif // _DEBUG
#define _f(i) for(i =0;i<4;i++)
#define for_all(a) _f(a[0]) _f(a[1]) _f(a[2]) _f(a[3]) _f(a[4]) _f(a[5]) _f(a[6]) _f(a[7]) _f(a[8])
//预处理
register int order[10][16] = {
	{1, 1, 0, 1, 1, 0, 0, 0, 0},
	{1, 1, 1, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 0, 1, 1, 0, 0, 0},
	{1, 0, 0, 1, 0, 0, 1, 0, 0},
	{0, 1, 0, 1, 1, 1, 0, 1, 0},
	{0, 0, 1, 0, 0, 1, 0, 0, 1},
	{0, 0, 0, 1, 1, 0, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 1, 1, 1},
	{0, 0, 0, 0, 1, 1, 0, 1, 1}
};
int main() {
	register int target[10] = { 0 };
	
	for (register int i = 0; i < 9; i++) {
		std::cin >> target[i];
		
		//将钟盘翻转，把要多少步才能将当前状态变到12点转化为要多少步将0点变到当前状态的镜面
		if (target[i] == 3) { target[i] = 1; }
		else if (target[i] == 1) { target[i] = 3; }
	}
	
	register int a[10] = { 0 }, ans[10] = { 0 };
	int sum = 0xffffff;
	//每个操作如果重复4次就会回到原位，没有必要
	//枚举每个操作的次数
	for_all(a) {
		register int tsum = 0;
		register int time[10] = { 0 };
		register bool c = false;
		
		for (register int i = 0; i < 9; i++) {
			tsum += a[i];
			
			for (register int j = 0; j < 9; j++) {
				//获取在每个操作后的time
				time[i] += a[j] * order[j][i];
			}
			
			//每个time都是目标状态
			//一个不是，就肯定不可行
			if (time[i] % 4 != target[i]) {
				c = true;
				break;
			}
		}
		
		if (c) { continue; }
		
		if (tsum < sum) {
			sum = tsum;
			memcpy(ans, a, sizeof(a));
		}
	}
	
	for (register int i = 0; i < 9; i++) {
		while (ans[i]--) { std::cout << i + 1 << " "; }
	}
	
	return 0;
}