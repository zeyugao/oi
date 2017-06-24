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
#define _m(x) memset(x,0,sizeof(x))
int ary;
char m[1001];
char a[1001];
int len;
bool check() {
	for (int i = 1, j = len; i <= j; i++, j--) {
		if (m[i] != m[j]) { return false; }
	}
	return true;
}
void _plus() {
	char c[1001];
	_m(c);
	int i;
	for (i = 1; i <= len; i++) {
		c[i] += m[i] + m[len - i + 1];
		c[i + 1] += c[i] / ary;
		c[i] %= ary;
	}
	if (c[i] != 0) {
		int j = 1;
		len = i;
		while (i > 0) {
			m[j++] = c[i--];
		}
	}
	else {
		i -= 1;
		int j = 1;
		len = i;
		while (i > 0) {
			m[j++] = c[i--];
		}
	}
}
int main() {
	cin >> ary >> a;
	_m(m);
	for (int i = 0; i < strlen(a); i++) {
		if (a[i] < 'A') {
			m[i + 1] = a[i] - '0';
		}
		else {
			m[i + 1] = a[i] - 'A' + 10;
		}
	}
	len = strlen(a);
	int times = 0;
	while (times <= 30) {
		_plus();
		if (check()) {
			printf_s("STEP=%d", times + 1);
			system("pause");
			return 0;
		}
		times++;
	}
	cout << "Impossible!";
	system("pause");
	return 0;
}