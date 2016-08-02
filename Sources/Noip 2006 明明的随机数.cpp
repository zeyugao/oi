#ifndef _DEBUG
#pragma GCC optimize(2)
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
using namespace std;
#endif // _DEBUG

int main() {
	int m,t,num[101];
	scanf_s("%d", &m);
	set<int> a;
	while (m--) {
		scanf_s("%d", &t);
		a.insert(t);
	}
	int aaa = 1;
	set<int>::iterator i;
	for (i = a.begin(); i != a.end(); i++)
		num[aaa++] = *i;
	printf_s("%d\n", a.size());
	for (int ai = 1; ai < a.size(); ai++)
		printf_s("%d ", num[ai]);
	printf_s("%d", num[a.size()]);
	system("pause");
	return 0;
}