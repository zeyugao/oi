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
	
	std::string str;
	int pos;
	std::cin >> str;
	pos = str.size() - 1;
	while (str[pos] == '0' || str[pos] == ' ') {
		pos--;
	}
	int end = 0;
	if (str[0] == '-') { std::cout << "-"; end = 1; }
	for (int i = pos; i >= end; i--) {
		std::cout << str[i];
	}
#ifdef  _DEBUG
	system("pause");
#endif //  _DEBUG
	return 0;
}
