
#ifndef _DEBUG
#pragma GCC optimize(3)
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
#include <set>
using namespace std;
#endif // _DEBUG
struct station {
	double dis, price;
};
bool cmp(station a,station b) {
	return a.dis < b.dis;
}
//Coded by myself
//从当前加油站往后找，如果最近的加油站距离大于d2*c 输出-1
//如果找到了比当前加油站油价更低的或相同的，则加刚好能到达该加油站的油
//否则，则加满油到相对油价最低的加油站
int main() {
	double d1, c, d2, p, sum = 0, left = 0;
	station all[106] = { 0 };
	memset(all, 0, sizeof(all));
	int n, j, local = 0;
	scanf_s("%lf%lf%lf%lf", &d1, &c, &d2, &p);
	scanf_s("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf_s("%lf%lf", &all[i].dis, &all[i].price);
	}
	all[0].dis = 0; all[n + 1].dis = d1;
	all[0].price = p; all[n + 1].price = 1000000.0;
	sort(all, all + n + 1, cmp);
	double max_dis = c*d2, min_price;
	for (int i = 0; i <= n;) {
		min_price = 10000000.0;
		if (all[i + 1].dis - all[i].dis>max_dis) { printf_s("-1");return 0; }
		local = i + 1;
		for (j = i + 1; j <= n + 1; j++ ) {
			if (all[j].dis - all[i].dis > max_dis) { break; }
			if (min_price > all[j].price) {
				min_price = all[j].price;
				local = j;
			}
			if (j == n + 1) {
				if (min_price > all[i].price) {
					sum+= (((all[j].dis - all[i].dis) / d2) - left)*all[i].price;
					left = 0;
					goto end;
				}
			}
		}
		if (min_price > all[i].price) {
			sum += (c - left)*all[i].price;
			left = c - (all[local].dis - all[i].dis) / d2;
		}
		else {
			sum += (((all[local].dis - all[i].dis) / d2) - left)*all[i].price;
			left = 0;
		}
		i = local;
	}
	end:
	printf_s("%.2lf\n", sum);
	return 0;
}