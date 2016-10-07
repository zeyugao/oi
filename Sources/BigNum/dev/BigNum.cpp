#include <iostream>
#include <fstream>
#include "BigNum.h"

BigNum::~BigNum() {}

BigNum::BigNum(const int b)
{
	int c, d = b;
	len = 0;
	memset(s, 0, sizeof(s));
	while (d > MAXN) {
		//用先除以一个数，在乘以一个数，利用int的特性，将末尾(len(那个数)的长度的)的数归为0，再用这个原数减去这个去掉这个被去末尾数，得到余数，避免了%的运算
		c = d - (d / (MAXN + 1))*(MAXN + 1);
		d = d / (MAXN + 1);
		s[len++] = c;
	}
	s[len++] = d;
}

BigNum::BigNum(const char *a)
{
	int t, k, index, l, i;
	memset(s, 0, sizeof(s));
	l = strlen(a);
	len = l / DLEN;
	if (l%DLEN)len++;
	index = 0;
	for (i = l - 1; i >= 0; i -= DLEN) {
		t = 0; k = i - DLEN + 1;
		if (k < 0)k = 0;
		for (int j = k; j <= i; j++)
			t = t * 10 + a[j] - '0';
		s[index++] = t;
	}
}

BigNum::BigNum(const BigNum &a) :len(a.len)
{
	memset(s, 0, sizeof(s));
	for (int i = 0; i < len; i++)
		s[i] = a.s[i];
}

BigNum & BigNum::operator=(const BigNum &a)
{
	len = a.len;
	memset(s, 0, sizeof(s));
	for (int i = 0; i < len; i++)
		s[i] = a.s[i];
	return *this;
}

std::istream & operator >> (std::istream &in, BigNum &a)
{
	char szTmp[MAXN * 4 + 4];
	in >> szTmp;
	int t, k, index, l, i;
	memset(a.s, 0, sizeof(a.s));
	l = strlen(szTmp);
	a.len = l / DLEN;
	if (l%DLEN)a.len++;
	index = 0;
	for (i = l - 1; i >= 0; i -= DLEN) {
		t = 0; k = i - DLEN + 1;
		if (k < 0)k = 0;
		for (int j = k; j <= i; j++)
			t = t * 10 + szTmp[j] - '0';
		a.s[index++] = t;
	}
	return in;
}

std::ostream & operator << (std::ostream &out, BigNum &a)
{
	cout << a.s[a.len - 1];
	for (int i = a.len - 2; i >= 0; i--)
		std::cout << a.s[i];
	return out;
}

BigNum BigNum::operator+(const BigNum&T)const {
	BigNum t(*this);
	int i, big;
	big = T.len > len ? T.len : len;
	for (int 0; i < big; i++) {
		t.s[i] += T.s[i];
		if (t.s[i] > MAXN) 
			t.s[i + 1]++, t.a[i] -= MAXN + 1;
	}
	if (t.s[big] != 0)t.len = big + 1;
	else t.len = big;
	return t;
}
BigNum BigNum::operator-(const BigNum & T)const {
	int big; bool flag; BigNum t1, t2;
	if (*this > T) { t1 = *this; t2 = T; flag = false; }
	else { t1 = T; t2 = *this; flag = true; }
	big = t1.len;
	for (int i = 0; i < big; i++) {
		if (t1.s[i] < t2.s[i]) {
			int j = i + 1;
			while (t1.s[j] == 0)j++;
		}
	}
}