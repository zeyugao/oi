#ifndef DEBUG
#pragma GCC optimize(3)
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>
#include <fstream>
#include <cmath>
#include <Windows.h>
#include <set>
using namespace std;
#endif // DEBUG
#define N 4000
class BigNumber;
typedef BigNumber BN;
#define m(a) memset(a,0,sizeof(a))
class BigNumber {
	int len, s[N];
public:
	BigNumber() { len = 1; m(s); };
	BN operator=(const  char*a) {
		len = strlen(a);
		m(s);
		for (int i = 0; i < len; i++)
			s[i] = a[len - i - 1] - '0';
		return *this;
	}
	BN operator=(const int num) {
		char _num[N];
		m(_num);m(s);
		sprintf_s(_num, "%d", num);
		*this = _num;
		return *this;
	}
	BigNumber(const int num) { *this = num; }
	BigNumber(const char*num) { *this = num; }
	BN operator+(const BN&a) {
		BN c;
		c.len = max(len, a.len) + 1;
		int x = 0;
		for (int i = 0; i < c.len; i++) {
			c.s[i] = s[i] + a.s[i] + x;
			x = c.s[i] / 10;
			c.s[i] %= 10;
		}
		if (c.s[c.len - 1] == 0)c.len--;
	}
	BN operator+=(const BN &a) {
		*this = *this + a;
		return *this;
	}
	BN operator*(const BN &a) {
		BN c;
		c.len = len + a.len;
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < a.len; j++) {
				c.s[i + j] += s[i]*a.s[j];
				c.s[i + j + 1] +=c.s[i+j]/ 10;
				c.s[i + j] %= 10;
			}
		}
		if (c.s[c.len - 1] == 0)c.len--;
		return c;
	}
	bool operator<(const BN &a) const {
		if (a.len != len)return len < a.len;
		for (int i = len - 1; i >= 0; --i)
			if (s[i] != a.s[i])return s[i] < a.s[i];
		return false;
	}
	bool operator>(const BN&a) { return a < *this; }

	//请注意正负号
	BN operator-(const BN& a) {
		BN c;
		int b_fu = false;
		if (*this < a) //cout << "-";
			b_fu = true;
		int i = 0;
		while (i < a.len || i < len) {
			if (s[i] < a.s[i]) {
				s[i] += 10;
				s[i + 1]--;
			}
			c.s[i] = s[i] - a.s[i];
			i++;
		}
		c.len = i;
		while (c.len > 0 && c.s[c.len] == 0)c.len--;
	}
	//Pilot projects using by #define Experimental
	#ifdef Experimental
	//There is something wrong with the function,error with "Try to reference a function of the deleted".
	//Fix it
	/*friend ostream operator<<(ostream &out, const BN &x) {
		for (int i = x.len; i >= 0; --i)
			cout << x.s[i];
		return out;
	}*/
	
	BN operator/(BN&a) {
		BN c;
		//使用多次减法模拟除法
		//一直被除数减去除数，直到剩下的小于除数，每减一次，i++
		//余数：“直到剩下的小于除数”的剩下的数，
		//商：i
		return c;
	}
	#endif // Experimental
};