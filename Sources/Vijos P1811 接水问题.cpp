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
class cmp {
  public:
	bool operator()(const int n1, const int n2) const {
		//如果前面的比后面的大，就交换
		return n1 > n2;
	}
};
int main() {
	std::ios_base::sync_with_stdio(false);
	std::priority_queue<long, std::vector<int>, cmp> time;
	int n, m, tmp;
	
	std::cin >> n >> m;
	
	for (int i = 1; i <= m; i++) { time.push(0); }
	
	for (int i = 1; i <= n; i++) {
		std::cin >> tmp;
		int t = time.top(); time.pop();
		time.push(t + tmp);
	}
	
	for (int i = 1; i < m; i++) {
		time.pop();
	}
	
	std::cout << time.top() << std::endl;
	return 0;
}
